/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#include "app.h"
#include "configparser.h"
#include "datainterface.h"

#include <SupportDefs.h>
#include <AboutWindow.h>
#include <Catalog.h>
#include <Alert.h>
#include <Screen.h>
#include <Resources.h>
#include <AppFileInfo.h>
#include <String.h>
#include <FindDirectory.h>

#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <sstream>
#include <array>



#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "App"


App::App()
	:
	BApplication("application/x-vnd.BlueSky-ShakeIt")
{
	//get settings directory path
	BPath settings_path;
	find_directory(B_USER_SETTINGS_DIRECTORY, &settings_path);
	BDirectory settings_directory(settings_path.Path());
	ConfigParser::Config().SetConfigDirectory(settings_directory);

	//create new settings file if it doesn`t exist
	if (!settings_directory.Contains("ShakeIt_settings",B_FILE_NODE))
	{
		ConfigParser::Config().CreateConfigFile();
	}

}


App::~App()
{

	delete fGameSound;
	delete fGameController;
}


void
App::MessageReceived(BMessage *msg)
{

	switch(msg->what)
	{

		case MW_GIVEUP_BUTTON_CLICKED:
		{
			end_game(ENDGAME_REASON_GIVENUP);
			break;
		}

		case TV_TIME_OVER:
		{
			end_game(ENDGAME_REASON_TIMEOVER);
			break;
		}


		case MW_MENU_SETTINGS_CLICKED:
		{
			SettingsWindow *settings_window = new SettingsWindow(DataInterface::Data().GetDataDirectoryPath());
			settings_window->CenterOnScreen();
			settings_window->Show();
			break;
		}

		case MW_GO_BUTTON_CLICKED:
		{
			start_game();
			break;
		}

		case SW_SETTINGS_SAVE:
		{

			const char *lang_str;
			int8 minimum_word_length;
			bool sound;

			bool must_save=false;

			if (msg->FindString("gamelanguage", &lang_str) == B_OK)
			{
				BString game_language(lang_str);
				ConfigParser::Config().SetGameLanguage(game_language);
				DataInterface::Data().GetDictionary(game_language, fDictionary);
				fGameController->SetDictionary(fDictionary);
				BString dice_file_path;
				dice_file_path << DataInterface::Data().GetDataDirectoryPath().Path() << "/languages/" << game_language << "/" << game_language << ".dice";
				fGameController->SetDiceFile(std::string(dice_file_path.String()));
				must_save=true;
			}

			if (msg->FindInt8("minimumwordlength", &minimum_word_length) == B_OK)
			{
				ConfigParser::Config().SetMinWordLength(minimum_word_length);
				fGameController->SetMinimumWordLength(minimum_word_length);
				must_save=true;
			}


			if (msg->FindBool("sound", &sound) == B_OK)
			{

				ConfigParser::Config().SetSound(sound);
				must_save=true;
			}


			if (must_save)
			{
				ConfigParser::Config().WriteConfigToFile();
				fMainWindow->PostMessage(MW_STATUSVIEW_UPDATE);
			}

			break;
		}


		default:
		{
			BApplication::MessageReceived(msg);
			break;
		}

	}

}


void
App::AboutRequested()
{

	BAboutWindow *aboutwindow = new BAboutWindow("ShakeIt", "application/x-vnd.BlueSky-ShakeIt");

	const char *authors[] =
	{
		"Andi Machovec (BlueSky)",
		NULL
	};

	BResources *appresource = BApplication::AppResources();
	size_t size;
	version_info *appversion = (version_info *)appresource->LoadResource('APPV',1,&size);
	BString version_string;
	version_string<<appversion->major;
	version_string+=".";
	version_string<<appversion->middle;
	version_string+=".";
	version_string<<appversion->minor;

	aboutwindow->AddCopyright(2017, "Andi Machovec");
	aboutwindow->AddAuthors(authors);
	aboutwindow->SetVersion(version_string.String());
	aboutwindow->AddDescription(B_TRANSLATE("a word searching game"));
	aboutwindow->AddExtraInfo("");
	aboutwindow->Show();

}


bool
App::QuitRequested()
{

	return true;

}


void
App::ReadyToRun()
{

	try
	{

		//initialize config parser and data interface
		ConfigParser::Config().ReadConfigFromFile();

		//create game controller
		int minimum_word_length = ConfigParser::Config().GetMinWordLength();
		BString game_language = ConfigParser::Config().GetGameLanguage();
		DataInterface::Data().GetDictionary(game_language, fDictionary);
		BString dice_file_path;
		dice_file_path << DataInterface::Data().GetDataDirectoryPath().Path() << "/languages/" << game_language << "/" << game_language << ".dice";
		fGameController = new GameController(fDictionary,std::string(dice_file_path.String()),minimum_word_length);

		//create sound player
		BString sound_file_path;
		sound_file_path << DataInterface::Data().GetDataDirectoryPath().Path() << "/shakeit.wav";
		fGameSound = new BSimpleGameSound(sound_file_path.String());
		fGameSound->SetIsLooping(false);

		//set app pulse to 1 second	(for the timer)
		SetPulseRate(1000000);

		//create and show the main, input and timer window
		BString mainwindow_title("ShakeIt");
		mainwindow_title.Append(" - ");
		mainwindow_title.Append(B_TRANSLATE("Game Board"));

		BString inputwindow_title("ShakeIt");
		inputwindow_title.Append(" - ");
		inputwindow_title.Append(B_TRANSLATE("Notepad"));

		BString timerwindow_title("ShakeIt");
		timerwindow_title.Append(" - ");
		timerwindow_title.Append(B_TRANSLATE("Timer"));

		BScreen *main_screen = new BScreen(B_MAIN_SCREEN_ID);
		BRect main_screen_frame = main_screen->Frame();
		delete main_screen;


		BSize mainwindow_size(440,400);
		BSize inputwindow_size(400,400);
		BSize timerwindow_size(200,80);


		const float horiz_dist_windows = 20;
		const float vert_dist_windows = 50;

		BPoint mainwindow_anchor((main_screen_frame.Width()-
					(mainwindow_size.Width()+horiz_dist_windows+inputwindow_size.Width())) / 2,150);
		BPoint inputwindow_anchor(main_screen_frame.Width()-
					mainwindow_anchor.x-inputwindow_size.Width(),150);
		BPoint timerwindow_anchor((main_screen_frame.Width()-timerwindow_size.Width()) / 2,
					mainwindow_anchor.y+mainwindow_size.Height()+vert_dist_windows);


		fMainWindow = new MainWindow(mainwindow_title, BRect(mainwindow_anchor,mainwindow_size), DataInterface::Data().GetDataDirectoryPath().Path());
		fInputWindow = new InputWindow(inputwindow_title, BRect(inputwindow_anchor,inputwindow_size));
		fTimerWindow = new TimerWindow(timerwindow_title, BRect(timerwindow_anchor,timerwindow_size));

		fMainWindow->Show();
		fInputWindow->Show();
		fTimerWindow->Show();
		fInputWindow->PostMessage(new BMessage(IW_TEXT_DISABLE_EDIT));
		fMainWindow->Activate(true);
	}


	catch(const std::runtime_error &e)
	{
		BAlert *error_alert = new BAlert("ShakeIt",e.what(),"OK");
		error_alert->Go();
		this->PostMessage(new BMessage(B_QUIT_REQUESTED));
	}

}


void
App::Pulse() //sends a message every second to update the timer
{

	if (fGameController->IsRoundRunning())
	{
		fTimerWindow->PostMessage(new BMessage(TW_TIMER_UPDATE));
	}
}




void
App::start_game()
{

	//disable the settings menu
	fMainWindow->PostMessage(new BMessage(MW_MENU_SETTINGS_DISABLE));

	//disable the go button
	fMainWindow->PostMessage(new BMessage(MW_GO_BUTTON_DISABLE));


	//play sound if activated
	if (ConfigParser::Config().GetSound() == true)
	{
		//play sound
		fGameSound->StartPlaying();

		//sleep while the sound is playing (because it is played asynchronously)
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}


	//tell the game controller to start the round
	fGameController->StartRound();

	//get the board data from the game controller, pack it into a message, and send it to the main window
	std::vector<std::string> board_letters=fGameController->GetBoardLetters();
	std::vector<int> board_letter_orientation=fGameController->GetBoardLetterOrientation();

	BMessage *board_setup_msg = new BMessage(MW_BOARD_SETUP);

	for (int i=0; i<16; ++i)
	{
			board_setup_msg->AddString("letter",board_letters[i].c_str());
			board_setup_msg->AddInt32("orientation", board_letter_orientation[i]);
	}

	fMainWindow->PostMessage(board_setup_msg);


	//start the timer
	fTimerWindow->PostMessage(new BMessage(TW_TIMER_START));


	//clear the input window and enable text input
	fInputWindow->PostMessage(new BMessage(IW_TEXT_ENABLE_EDIT));
	fInputWindow->PostMessage(new BMessage(IW_TEXT_CLEAR));

	//activate the input window
	fInputWindow->PostMessage(new BMessage(IW_ACTIVATE));


	//enable the giveup button
	fMainWindow->PostMessage(new BMessage(MW_GIVEUP_BUTTON_ENABLE));

}




void
App::end_game(int reason)
{
	//stop the timer
	fTimerWindow->PostMessage(new BMessage(TW_TIMER_STOP));


	//disable text editing on the input window
	fInputWindow->PostMessage(new BMessage(IW_TEXT_DISABLE_EDIT));


	//inform the user that the time is over
	if (reason == ENDGAME_REASON_TIMEOVER)
	{
		BAlert *time_over_alert = new BAlert("ShakeIt",B_TRANSLATE("Time over"),"OK");
		time_over_alert->Go();
	}

	//get the word list from InputWindow object
	std::vector<std::string>::iterator iter;
	std::vector<std::string> word_list = fInputWindow->GetWordList();


	//give the word list to the gamecontroller for evaluation
	fGameController->SetWordList(word_list);


	//Let the GameController evaluate the words and get back the results
	round_results results=fGameController->RoundFinished();


	//get the missing words from the gamecontroller
	std::vector<std::string> missing_words = fGameController->GetMissingWords();

	//assign status messages for the word evaluation
	std::array<std::string,5> result_text;
	result_text[0]=B_TRANSLATE("OK");
	result_text[1]=B_TRANSLATE("too short");
	result_text[2]=B_TRANSLATE("not possible");
	result_text[3]=B_TRANSLATE("not in dictionary");
	result_text[4]=B_TRANSLATE("duplicate");



	//Display the results on the input window
	std::stringstream result_stream;

	for (unsigned int i=0; i < word_list.size(); ++i)
	{

		int result_code = results[i].first;
		int result_points = results[i].second;



		if (result_code == 0)  //display the valid word along with the given points
		{
			result_stream << word_list[i] << " (" << result_points << ")\n";
		}

		else	//display invalid word in red along with the reason why they´re invalid
		{
			result_stream << word_list[i] << " (" << result_text[result_code] << ")\n";
		}

	}

	//total points in this round
	result_stream << "\n" << B_TRANSLATE("Points in this round") << ": " << fGameController->GetCurrentRoundPoints() << "\n";


	//missing words
	if (!missing_words.empty())
	{

		result_stream << "\n\n";
		result_stream << B_TRANSLATE("Missing words") << ":\n";

		std::vector<std::string>::iterator mw_iter;

		for (mw_iter=missing_words.begin();mw_iter!=missing_words.end();++mw_iter)
		{
			result_stream << *mw_iter << "\n";
		}

	}

	BMessage *result_display_message=new BMessage(IW_TEXT_SHOW);
	result_display_message->AddString("text",result_stream.str().c_str());
	fInputWindow->PostMessage(result_display_message);


	//enable the go button and disable the giveup button
	fMainWindow->PostMessage(new BMessage(MW_GO_BUTTON_ENABLE));
	fMainWindow->PostMessage(new BMessage(MW_GIVEUP_BUTTON_DISABLE));


	//enable the settings menu again
	//disable the settings menu
	fMainWindow->PostMessage(new BMessage(MW_MENU_SETTINGS_ENABLE));

}


int
main(int argc, char **argv)
{

	App *haiku_app = new App();
	haiku_app->Run();

	delete haiku_app;

	return 0;

}

#include "app.h"

#include <SupportDefs.h>
#include <AboutWindow.h>
#include <Catalog.h>
#include <Alert.h>

#include <iostream>

//----------------------------------------------------------------------------
App::App()
		: BApplication(APP_SIGNATURE)
//----------------------------------------------------------------------------
{

	resource_dir="/boot/home/config/settings/Boggle"; 

}	



//----------------------------------------------------------------------------
void App::MessageReceived(BMessage *msg)
//----------------------------------------------------------------------------
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
			SettingsWindow *settings_window = new SettingsWindow();		
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
			
			const char *game_language;
			const char **p_gl = &game_language;
			int8 minimum_word_length; 
			int8 *p_mwl = &minimum_word_length;
			
			bool sound;
			bool *p_sound=&sound;
			
			bool must_save=false;
			
			if (msg->FindString("gamelanguage", p_gl) == B_OK)
			{
				std::string game_language_str(game_language);
				ConfigParser::Config().SetParameter("game_language",game_language_str);
				game_controller->SetDictionaryFile(resource_dir+"/languages/"+game_language_str+"/"+game_language_str+".dict");
				game_controller->SetDiceFile(resource_dir+"/languages/"+game_language_str+"/"+game_language_str+".dice");
				must_save=true;
			}		
			
			if (msg->FindInt8("minimumwordlength", p_mwl) == B_OK)
			{
				ConfigParser::Config().SetParameter("minimum_word_length",std::to_string(minimum_word_length));
				game_controller->SetMinimumWordLength(minimum_word_length);
				must_save=true;
			}
				
				
			if (msg->FindBool("sound", p_sound) == B_OK)	
			{
						
				if (sound) 
				{
					ConfigParser::Config().SetParameter("sound","on");
				}
				else
				{
					ConfigParser::Config().SetParameter("sound","off");
				}		
				
				must_save=true;	
			}	
				
				
			if (must_save)
			{
				ConfigParser::Config().WriteConfigToFile(resource_dir+"/boggle.xml");	
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



//----------------------------------------------------------------------------
void App::AboutRequested()
//----------------------------------------------------------------------------
{
	
	BAboutWindow *aboutwindow = new BAboutWindow(APPTITLE, APP_SIGNATURE);
	
	const char *authors[] =
	{
		APPAUTHOR,
		NULL
	};
	
	
	aboutwindow->AddCopyright(APPCOPYRIGHTYEAR, APPCOPYRIGHTNAME);
	aboutwindow->AddAuthors(authors);
	aboutwindow->SetVersion(APPVERSION);
	aboutwindow->AddDescription(B_TRANSLATE(APPDESCRIPTION));
	aboutwindow->AddExtraInfo(B_TRANSLATE(APPEXTRAINFO));
	//aboutwindow->AddSpecialThanks("APPSPECIALTHANKS");
	aboutwindow->Show();
	
}



//----------------------------------------------------------------------------
bool App::QuitRequested()
//----------------------------------------------------------------------------
{
	
	return true; 
	
}



//----------------------------------------------------------------------------
void App::ReadyToRun()
//----------------------------------------------------------------------------
{

	
	
	try
	{
		
		//initialize config parser 
		ConfigParser::Config().ReadConfigFromFile("/boot/home/config/settings/Boggle/boggle.xml");
		
		
		//create game controller
		int minimum_word_length=std::stoi(ConfigParser::Config().GetParameter("minimum_word_length"));
		std::string language=(ConfigParser::Config().GetParameter("game_language"));
		std::string dictionary_file=resource_dir+"/languages/"+language+"/"+language+".dict";
		std::string dice_file=resource_dir+"/languages/"+language+"/"+language+".dice";
		
		game_controller = new GameController(dictionary_file,dice_file,minimum_word_length);
		
		
		//create sound player
		sound_player = new SoundPlayer(resource_dir+"/boggle.wav");
		
	
		//set app pulse to 1 second	(for the timer)
		SetPulseRate(1000000);	
	
	
		//create and show the main and the input window
		main_window = new MainWindow("Boggle - Game Board", BRect(100,100,540,500));
	
		BRect main_window_rect = main_window->Frame();
		
		input_window = new InputWindow("Boggle - Input Window" ,BRect(main_window_rect.right+20,100,main_window_rect.right+420,500));
		main_window->Show();
		input_window->Show();
		input_window->PostMessage(new BMessage(IW_TEXT_DISABLE_EDIT));
		main_window->Activate(true);
	}


	catch(const std::runtime_error &e)
	{
		BAlert *error_alert = new BAlert("Boggle",e.what(),"OK");
		error_alert->Go();
		this->PostMessage(new BMessage(B_QUIT_REQUESTED));
	}	

}	



//----------------------------------------------------------------------------
void App::Pulse() //sends a message every second to update the timer
//----------------------------------------------------------------------------
{

	if (game_controller->IsRoundRunning())
	{
		main_window->PostMessage(new BMessage(MW_TIMER_UPDATE));
	}
}



//----------------------------------------------------------------------------
void App::start_game()
//----------------------------------------------------------------------------
{
	
	//disable the settings menu
	main_window->PostMessage(new BMessage(MW_MENU_SETTINGS_DISABLE));
	
	//disable the go button and enable the givup button
	main_window->PostMessage(new BMessage(MW_GO_BUTTON_DISABLE));
	main_window->PostMessage(new BMessage(MW_GIVEUP_BUTTON_ENABLE));
	
	
	//clear the input window and enable text input
	input_window->PostMessage(new BMessage(IW_TEXT_ENABLE_EDIT));
	input_window->PostMessage(new BMessage(IW_TEXT_CLEAR));
	
	
	//play sound if activated
	if (ConfigParser::Config().GetParameter("sound") == "on")
	{ 
		sound_player->Play();
	}
	
	//activate the input window
	input_window->PostMessage(new BMessage(IW_ACTIVATE));
	
	
	//tell the game controller to start the round
	game_controller->StartRound();
	
	
	//get the board data from the game controller, pack it into a message, and send it to the main window
	std::vector<std::string> board_letters=game_controller->GetBoardLetters();
	std::vector<int> board_letter_orientation=game_controller->GetBoardLetterOrientation();
	 
	BMessage *board_setup_msg = new BMessage(MW_BOARD_SETUP); 
	 
	for (int i=0; i<16; ++i)
	{
			board_setup_msg->AddString("letter",board_letters[i].c_str());
			board_setup_msg->AddInt32("orientation", board_letter_orientation[i]);
	}	
	
	main_window->PostMessage(board_setup_msg);
	
	
	//start the timer
	main_window->PostMessage(new BMessage(MW_TIMER_START));
	
}	



//----------------------------------------------------------------------------
void App::end_game(int reason)
//----------------------------------------------------------------------------
{
	//stop the timer
	main_window->PostMessage(new BMessage(MW_TIMER_STOP));

	
	//disable text editing on the input window
	input_window->PostMessage(new BMessage(IW_TEXT_DISABLE_EDIT));

	
	//inform the user that the time is over
	if (reason == ENDGAME_REASON_TIMEOVER)
	{
		BAlert *time_over_alert = new BAlert("Boggle",B_TRANSLATE("Time over"),"OK");
		time_over_alert->Go();
	}
	
	//get the word list from InputWindow object
	std::vector<std::string>::iterator iter;
	std::vector<std::string> word_list = input_window->GetWordList();

	
	//give the word list to the gamecontroller for evaluation
	game_controller->SetWordList(word_list);

	
	//Let the GameController evaluate the words and get back the results
	round_results results=game_controller->RoundFinished();

	
	//get the missing words from the gamecontroller
	std::vector<std::string> missing_words = game_controller->GetMissingWords();
	
	//assign status messages for the word evaluation
	std::array<std::string,5> result_text;
	result_text[0]=B_TRANSLATE("OK");
	result_text[1]=B_TRANSLATE("too short");
	result_text[2]=B_TRANSLATE("not possible");
	result_text[3]=B_TRANSLATE("not in dictionary");
	result_text[4]=B_TRANSLATE("duplicate");

	
	
	//Display the results on the input window
	std::stringstream result_stream;
	
	for (int i=0; i < word_list.size(); ++i)
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
	result_stream << "\n" << B_TRANSLATE("Points in this round") << ": " << game_controller->GetCurrentRoundPoints() << "\n";
	
	
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
	input_window->PostMessage(result_display_message);
	
	
	//enable the go button and disable the giveup button
	main_window->PostMessage(new BMessage(MW_GO_BUTTON_ENABLE));
	main_window->PostMessage(new BMessage(MW_GIVEUP_BUTTON_DISABLE));
	
	
	//enable the settings menu again
	//disable the settings menu
	main_window->PostMessage(new BMessage(MW_MENU_SETTINGS_ENABLE));
	
}	



//----------------------------------------------------------------------------
int main(int argc, char **argv)
//----------------------------------------------------------------------------
{
	
	App *haiku_app = new App();
	haiku_app->Run();
	
	delete haiku_app;
	
	return 0;
	
}	

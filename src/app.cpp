#include "app.h"


//----------------------------------------------------------------------------
App::App(void)
		: BApplication(APP_SIGNATURE)
//----------------------------------------------------------------------------
{
}	



//----------------------------------------------------------------------------
void App::MessageReceived(BMessage *msg)
//----------------------------------------------------------------------------
{
	
	switch(msg->what)
	{
		
		case TV_TIME_OVER:
		{
			end_game();	
			break;
		}
			
		
		case MW_MENU_SETTINGS_CLICKED:
		{
			SettingsWindow *settings_window = new SettingsWindow(config_parser->GetParam("dictionary_file"),config_parser->GetParam("minimum_word_length"));		
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
			
			const char *dictionary_file = msg->FindString("dictionaryfile");
			const char *minimum_word_length = msg->FindString("minimumwordlength");
			
			bool must_save=false;
			
			if (dictionary_file != NULL)
			{
				config_parser->SetParam("dictionary_file",std::string(dictionary_file));
				game_controller->SetDictionaryFile(std::string(dictionary_file));
				must_save=true;
			}		
			
			if (minimum_word_length != NULL)
			{
				config_parser->SetParam("minimum_word_length",std::string(minimum_word_length));
				game_controller->SetMinimumWordLength(std::atoi(minimum_word_length));
				must_save=true;
			}
				
			if (must_save)
			{
				config_parser->WriteConfig();	
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
		
		//initialize config parser and game controller
		config_parser=new ConfigParser(CONFIG_FILE);
	
		std::string dictionary_file = config_parser->GetParam("dictionary_file");
		int minimum_word_length = std::stoi(config_parser->GetParam("minimum_word_length"));
		game_controller = new GameController(dictionary_file, minimum_word_length);
	
	
		//set app pulse to 1 second	(for the timer)
		SetPulseRate(1000000);	
	
	
		//create and show the main and the input window
		main_window = new MainWindow(100,100,620,500);
	
		BRect main_window_rect = main_window->Frame();
	
		input_window = new InputWindow(main_window_rect.right+20,100,main_window_rect.right+420,500);
		main_window->Show();
		input_window->Show();
		input_window->PostMessage(new BMessage(IW_TEXT_DISABLE_EDIT));
		main_window->Activate(true);
	}


	catch(const std::runtime_error &e)
	{
		BAlert *time_over_alert = new BAlert("Boggle",e.what(),"OK");
		time_over_alert->Go();
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
	
	//disable the go button
	main_window->PostMessage(new BMessage(MW_GO_BUTTON_DISABLE));
	
	//clear the input window and enable text input
	input_window->PostMessage(new BMessage(IW_TEXT_ENABLE_EDIT));
	input_window->PostMessage(new BMessage(IW_TEXT_CLEAR));
	
	
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
void App::end_game()
//----------------------------------------------------------------------------
{
	//stop the timer
	main_window->PostMessage(new BMessage(MW_TIMER_STOP));

	
	//disable text editing on the input window
	input_window->PostMessage(new BMessage(IW_TEXT_DISABLE_EDIT));

	
	//inform the user that the time is over
	BAlert *time_over_alert = new BAlert("Boggle",B_TRANSLATE("Time over"),"OK");
	time_over_alert->Go();

	
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
	
	
	//enable the go button again
	main_window->PostMessage(new BMessage(MW_GO_BUTTON_ENABLE));
	
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

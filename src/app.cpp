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
			main_window->PostMessage(msg);	
			break;
		}
			
		
		case MW_SETTINGS_MENU:
		{
			SettingsWindow *settings_window = new SettingsWindow();		
			settings_window->CenterOnScreen();
			settings_window->Show();
			break;
		}
		
		case MW_GO_BUTTON:
		{
			start_game();
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

	//create GameController object
	game_controller = new GameController("/boot/home/Development/Boggle/data/dictionary.txt");
	
	//set app pulse to 1 second	
	SetPulseRate(1000000);	
	
	//create and show the main and the input window
	main_window = new MainWindow();
	input_window = new InputWindow();
	main_window->Show();
	input_window->Show();
	input_window->PostMessage(new BMessage(IW_TEXT_DISABLE_EDIT));

}	


//----------------------------------------------------------------------------
void App::Pulse()
//----------------------------------------------------------------------------
{

	if (game_controller->IsRoundRunning())
	{
		std::cout << "Määhhhh" << std::endl;
	}
}

//----------------------------------------------------------------------------
void App::start_game()
//----------------------------------------------------------------------------
{
	std::cout << "Disabling Go Button" << std::endl;
	
	main_window->PostMessage(new BMessage(MW_DISABLE_GO_BUTTON));
	
	input_window->PostMessage(new BMessage(IW_TEXT_ENABLE_EDIT));
	input_window->PostMessage(new BMessage(IW_TEXT_CLEAR));
	
	
	std::cout << "Starting Round" << std::endl;
	game_controller->StartRound();
	
	//letter_view->SetLetters(game_controller->GetBoardLetters(),game_controller->GetBoardLetterOrientation());
	//timer_view->StartTimer();
	
}	



//----------------------------------------------------------------------------
void App::end_game()
//----------------------------------------------------------------------------
{
	

	//input_window->SetTextInactive();
	
	//inform the user that the time is over
	BAlert *time_over_alert = new BAlert("Boggle","Time over","OK");
	time_over_alert->Go();
	
	//get the word list from InputWindow object
	std::vector<std::string>::iterator iter;
	std::vector<std::string> word_list = input_window->GetWordList();
	
	//give the word list to the gamecontroller for evaluation
	game_controller->SetWordList(word_list);
	
	//Let the GameController evaluate the words and get back the results
	round_results results=game_controller->RoundFinished();
	std::vector<std::string> missing_words = game_controller->GetMissingWords();

	//Display the results on the input window
	input_window->DisplayResults(results, game_controller->GetCurrentRoundPoints(), missing_words);

	//enable the go button again
	//main_window->EnableGoButton();
	
	
	
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

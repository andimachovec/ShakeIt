#include "mainwindow.h"

//----------------------------------------------------------------------------
MainWindow::MainWindow(void)
	:BWindow(BRect(100,100,620,500),APPTITLE, B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS)
//----------------------------------------------------------------------------
{
	
	//initialize GUI Objects
	top_menu_bar = new BMenuBar("topmenubar");
	letter_view = new LetterView();
	go_button = new BButton("Go", new BMessage(MW_GO_BUTTON));
	
	input_window = new InputWindow();
	timer_view = new TimerView();
	
	
	//build the menu layout
	BLayoutBuilder::Menu<>(top_menu_bar)
		.AddMenu(B_TRANSLATE("File"))
			.AddItem(B_TRANSLATE("Settings"), MW_SETTINGS_MENU, 'S')
			.AddItem(B_TRANSLATE("Quit"), B_QUIT_REQUESTED, 'Q')
		.End()
		.AddMenu(B_TRANSLATE("Help"))
			.AddItem(B_TRANSLATE("About"), MW_ABOUT)
		.End()
	.End();	
		
	
	//build the main layout
	BLayoutBuilder::Group<>(this, B_VERTICAL,0)
		.SetInsets(0)
		.Add(top_menu_bar)
		.AddGroup(B_HORIZONTAL,50)
			.Add(letter_view)
		.End()	
		.AddGroup(B_HORIZONTAL,0)	
			.Add(go_button)
			.Add(timer_view)	
		.End()
	.Layout();	
		
	
	input_window->Show();
	input_window->SetTextInactive();
	
	game_controller = new GameController("/boot/home/Development/Boggle/data/dictionary.txt");
	

}


//----------------------------------------------------------------------------
void MainWindow::MessageReceived(BMessage *msg)
//----------------------------------------------------------------------------
{
	
	switch (msg->what)	
	{
		
		
		
		case MW_ABOUT:
		{
			be_app->PostMessage(B_ABOUT_REQUESTED);
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
		
		case TV_TIME_OVER:
		{
			end_game();	
			break;
		}	
		
						
		default:
		{
			BWindow::MessageReceived(msg);
			break;
		}
	}

}	



//----------------------------------------------------------------------------
bool MainWindow::QuitRequested(void)
//----------------------------------------------------------------------------
{
	
	be_app->PostMessage(B_QUIT_REQUESTED);	
	return true;
}	



//----------------------------------------------------------------------------
void MainWindow::start_game()
//----------------------------------------------------------------------------
{
	
	go_button->SetEnabled(false);
	
	input_window->SetTextActive();
	input_window->ClearText();
	
	game_controller->StartRound();
	
	letter_view->SetLetters(game_controller->GetBoardLetters(),game_controller->GetBoardLetterOrientation());
	timer_view->StartTimer();
	
}	



//----------------------------------------------------------------------------
void MainWindow::end_game()
//----------------------------------------------------------------------------
{
	
	std::cout << "Deactivating text input..." << std::endl;
	input_window->SetTextInactive();
	
	//inform the user that the time is over
	std::cout << "Display time over message..." << std::endl;
	BAlert *time_over_alert = new BAlert("Boggle","Time over","OK");
	time_over_alert->Go();
	
	//get the word list from InputWindow object
	
	std::cout << "Calling InputWindow::GetWordList..." << std::endl;
	std::vector<std::string>::iterator iter;
	std::vector<std::string> word_list = input_window->GetWordList();
	
	//give the word list to the gamecontroller for evaluation
	std::cout << "Calling GameController::SetWordList..." << std::endl;
	game_controller->SetWordList(word_list);
	
	
	//Let the GameController evaluate the words and get back the results
	std::cout << "Calling GameController::RoundFinished..." << std::endl;
	round_results results=game_controller->RoundFinished();
	
	
	std::cout << "Calling GameController::GetMissingWords..." << std::endl;
	std::vector<std::string> missing_words = game_controller->GetMissingWords();

	//Display the results on the input window
	std::cout << "Calling InputWindow::DisplayResults..." << std::endl;
	input_window->DisplayResults(results, game_controller->GetCurrentRoundPoints(), missing_words);

	
	go_button->SetEnabled(true);
	
	
}	





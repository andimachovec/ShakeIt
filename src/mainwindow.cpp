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
		.AddGroup(B_HORIZONTAL)
			.Add(letter_view)
			//.Add(go_button)	
		.End()	
		.AddGroup(B_HORIZONTAL)
			.Add(go_button)
		.End()	
	.Layout();	
		
	
	input_window->Show();
	
	game_controller = new GameController("../data/dictionary.txt");
	

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
	//input_window->ClearText();
	//input_window->SetTextActive();
	
	game_controller->StartRound();
	
	letter_view->SetLetters(game_controller->GetBoardLetters(),game_controller->GetBoardLetterOrientation());
	
}	




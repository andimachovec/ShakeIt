#include "mainwindow.h"

//----------------------------------------------------------------------------
MainWindow::MainWindow()
	:BWindow(BRect(100,100,620,500),APPTITLE, B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS)
//----------------------------------------------------------------------------
{
	
	//initialize GUI Objects
	top_menu_bar = new BMenuBar("topmenubar");
	letter_view = new LetterView();
	go_button = new BButton("Go", new BMessage(MW_GO_BUTTON_CLICKED));
	
	timer_view = new TimerView();
	
	
	//build the menu layout
	BLayoutBuilder::Menu<>(top_menu_bar)
		.AddMenu(B_TRANSLATE("File"))
			.AddItem(B_TRANSLATE("Settings"), MW_MENU_SETTINGS, 'S')
			.AddItem(B_TRANSLATE("Quit"), B_QUIT_REQUESTED, 'Q')
		.End()
		.AddMenu(B_TRANSLATE("Help"))
			.AddItem(B_TRANSLATE("About"), MW_MENU_ABOUT)
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
		
		
}


//----------------------------------------------------------------------------
void MainWindow::MessageReceived(BMessage *msg)
//----------------------------------------------------------------------------
{
	
	switch (msg->what)	
	{
		
		
		
		case MW_MENU_ABOUT:
		{
			be_app->PostMessage(B_ABOUT_REQUESTED);
			break;	
		}		
		
		
		case MW_MENU_SETTINGS:
		{
			be_app->PostMessage(msg);
			break;
		}
				
				
		case MW_GO_BUTTON_CLICKED:
		{
			be_app->PostMessage(msg);	
			break;
		}
		
		case TV_TIME_OVER:
		{
			//end_game();	
			break;
		}	
		
		
		case MW_GO_BUTTON_ENABLE:
		{
			go_button->SetEnabled(true);
			break;
		}	
		
		
		case MW_GO_BUTTON_DISABLE:
		{
			go_button->SetEnabled(false);
			break;
		}	
		
		case MW_TIMER_UPDATE:
		{
			timer_view->UpdateTimer();
			break;	
		}	
		
		case MW_TIMER_START:
		{
			timer_view->StartTimer();
			break;	
		}	
		
		
		case MW_TIMER_STOP:
		{
			timer_view->StopTimer();
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
bool MainWindow::QuitRequested()
//----------------------------------------------------------------------------
{
	
	be_app->PostMessage(B_QUIT_REQUESTED);	
	return true;
}	





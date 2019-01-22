#include "mainwindow.h"

#include <Application.h>
#include <Alert.h>
#include <StatusBar.h>
#include <TextControl.h>
#include <LayoutBuilder.h>
#include <Layout.h>
#include <LayoutItem.h>
#include <Catalog.h>
#include <Menu.h>
#include <MenuItem.h>


#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "MainWindow"


MainWindow::MainWindow(std::string title, BRect frame)
	:
	BWindow(frame, title.c_str(), B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS)
{
	
	//initialize GUI Objects
	fTopMenubar = new BMenuBar("topmenubar");
	fLetterView = new LetterView();
	fGoButton = new BButton(B_TRANSLATE("Shake it, baby!"), new BMessage(MW_GO_BUTTON_CLICKED));
	fGiveupButton = new BButton(B_TRANSLATE("Give Up"), new BMessage(MW_GIVEUP_BUTTON_CLICKED));
	fGiveupButton->SetEnabled(false);
	fTimerView = new TimerView();
	
	
	//build the menu layout
	BLayoutBuilder::Menu<>(fTopMenubar)
		.AddMenu(B_TRANSLATE("File"))
			.AddItem(B_TRANSLATE("Settings"), MW_MENU_SETTINGS_CLICKED, 'S')
			.AddItem(B_TRANSLATE("Quit"), B_QUIT_REQUESTED, 'Q')
		.End()
		.AddMenu(B_TRANSLATE("Help"))
			.AddItem(B_TRANSLATE("About"), MW_MENU_ABOUT_CLICKED)
		.End()
	.End();	
		
	
	//build the main layout
	BLayoutBuilder::Group<>(this, B_VERTICAL,0)
		.SetInsets(0)
		.Add(fTopMenubar)
		.AddGroup(B_VERTICAL)
			.Add(fLetterView,20)
			.AddGroup(B_HORIZONTAL,3)
				.Add(fGoButton)
				.Add(fGiveupButton)
			.End()	
			//.Add(fTimerView,1)	
		.End()
	.Layout();	
		
	
	fGameRunning=false;	
}


void 
MainWindow::MessageReceived(BMessage *msg)
{
	
	switch (msg->what)	
	{
		
		case MW_MENU_ABOUT_CLICKED:
		{
			be_app->PostMessage(B_ABOUT_REQUESTED);
			break;	
		}		
		
		
		case MW_MENU_SETTINGS_CLICKED:
		{
			be_app->PostMessage(msg);
			break;
		}
				
				
		case MW_GO_BUTTON_CLICKED:
		{
			be_app->PostMessage(msg);	
			break;
		}
		
		
		case MW_MENU_SETTINGS_ENABLE:
		{
			BMenuItem *settings_menu=fTopMenubar->FindItem(MW_MENU_SETTINGS_CLICKED);
			settings_menu->SetEnabled(true);
			break;
		}	
		
		
		case MW_MENU_SETTINGS_DISABLE:
		{
			BMenuItem *settings_menu=fTopMenubar->FindItem(MW_MENU_SETTINGS_CLICKED);
			settings_menu->SetEnabled(false);
			break;
		}
		
		
		case MW_GO_BUTTON_ENABLE:
		{
			fGoButton->SetEnabled(true);
			fGameRunning=false;
			break;
		}			
		
		case MW_GO_BUTTON_DISABLE:
		{
			fGoButton->SetEnabled(false);
			fGameRunning=true;
			break;
		}	
		
		case MW_GIVEUP_BUTTON_CLICKED:
		{
			be_app->PostMessage(msg);	
			break;
		}
		
		case MW_GIVEUP_BUTTON_ENABLE:
		{
			fGiveupButton->SetEnabled(true);	
			break;
		}	
		
		case MW_GIVEUP_BUTTON_DISABLE:
		{
			fGiveupButton->SetEnabled(false);	
			break;
		}	
		
		case MW_TIMER_UPDATE:
		{
			fTimerView->UpdateTimer();
			break;	
		}	
		
		case MW_TIMER_START:
		{
			fTimerView->StartTimer();
			break;	
		}	
		
		
		case MW_TIMER_STOP:
		{
			fTimerView->StopTimer();
			break;
		}
		
		
		case MW_BOARD_SETUP:
		{
			
			
			//get board data from message
			std::vector<std::string> board_letters;
			std::vector<int> board_letter_orientation;
				
			for (int i=0; i<16; ++i)
			{
				board_letters.push_back(std::string(msg->GetString("letter",i,NULL)));
				board_letter_orientation.push_back(msg->GetInt32("orientation",i,0));	
			}	
			
			//pass the board data to the letter view
			fLetterView->SetLetters(board_letters,board_letter_orientation);
			
			break;	
		}	
		
						
		default:
		{
			BWindow::MessageReceived(msg);
			break;
		}
	
	
	}

}	


bool 
MainWindow::QuitRequested()
{
	bool do_quit=true;
	
	if (fGameRunning)
	{
		
		BAlert *quit_alert = new BAlert("Boggle",
										B_TRANSLATE("Game still in progress. Do you really want to quit?"),
										B_TRANSLATE("Yes"),
										B_TRANSLATE("No"));
		if (quit_alert->Go() == 1)								
		{	
			do_quit=false;
		}		
	}	 
	
	if (do_quit)
	{
		be_app->PostMessage(B_QUIT_REQUESTED);	
	}
	
	return do_quit;
}	


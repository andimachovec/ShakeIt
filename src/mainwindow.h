#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <Window.h>
#include <MenuBar.h>
#include <PopUpMenu.h>
#include <Button.h>

#include <string>
#include <iostream>

#include "defs.h"
#include "letterview.h"
#include "timerview.h"


enum  
{
	MW_MENU_ABOUT_CLICKED = 'mw00',
	MW_MENU_SETTINGS_CLICKED,
	MW_MENU_SETTINGS_ENABLE,
	MW_MENU_SETTINGS_DISABLE,
	MW_GO_BUTTON_CLICKED,
	MW_GO_BUTTON_ENABLE,
	MW_GO_BUTTON_DISABLE,
	MW_GIVEUP_BUTTON_CLICKED,
	MW_GIVEUP_BUTTON_ENABLE,
	MW_GIVEUP_BUTTON_DISABLE,
	MW_TIMER_UPDATE,
	MW_TIMER_START,
	MW_TIMER_STOP,
	MW_BOARD_SETUP,
};	


class MainWindow : public BWindow {
public:
	
	MainWindow(std::string title, BRect frame);
	void MessageReceived(BMessage *msg);
	bool QuitRequested();
		
private:
		
	BMenuBar	*fTopMenubar;
	LetterView	*fLetterView;
	BButton		*fGoButton;
	BButton		*fGiveupButton;
	TimerView	*fTimerView;
		
	bool fGameRunning;
		
};


#endif

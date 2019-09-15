/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */
 
#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <Window.h>
#include <MenuBar.h>
#include <PopUpMenu.h>
#include <Button.h>

#include <string>

#include "letterview.h"
#include "statusview.h"


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
	MW_BOARD_SETUP,
	MW_STATUSVIEW_UPDATE
};	


class MainWindow : public BWindow {
public:
	
	MainWindow(std::string title, BRect frame, std::string DataDirectory);
	void MessageReceived(BMessage *msg);
	bool QuitRequested();
		
private:
		
	BMenuBar	*fTopMenubar;
	LetterView	*fLetterView;
	BButton		*fGoButton;
	BButton		*fGiveupButton;
	StatusView	*fStatusView;		
	bool 		fGameRunning;
		
};


#endif

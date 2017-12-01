#ifndef MAINWINDOW_H
#define MAINWINDOW_H


//Haiku API
#include <Application.h>
#include <Window.h>
#include <MenuBar.h>
#include <Menu.h>
#include <MenuItem.h>
#include <PopUpMenu.h>
#include <Button.h>
#include <StatusBar.h>
#include <TextControl.h>
#include <LayoutBuilder.h>
#include <Layout.h>
#include <LayoutItem.h>
#include <Catalog.h>
#include <Alert.h>


//other system includes
#include <string>
#include <iostream>


//local includes
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


class MainWindow : public BWindow
{
	
	public:
		MainWindow(float left, float top, float right, float bottom);
		void MessageReceived(BMessage *msg);
		bool QuitRequested();
		
	private:
		
		//GUI elements
		BMenuBar	*top_menu_bar;
		LetterView	*letter_view;
		BButton		*go_button;
		BButton		*giveup_button;
		TimerView	*timer_view;
		
};


#endif

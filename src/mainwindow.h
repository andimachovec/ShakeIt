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
#include "inputwindow.h"


#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "MainWindow"


enum WhatCodes 
{
	MW_ABOUT = 'mw00',
	MW_GO_BUTTON,
};	


class MainWindow : public BWindow
{
	
	public:
		MainWindow(void);
		void MessageReceived(BMessage *msg);
		bool QuitRequested(void);
		

	private:
		
		//GUI elements
		BMenuBar	*top_menu_bar;
		InputWindow	*input_window;
		LetterView	*letter_view;
		BButton		*go_button;
		
		
		
		
		//methods
		
		
};

#endif

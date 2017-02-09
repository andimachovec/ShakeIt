#ifndef APP_H
#define APP_H


//Haiku API includes
#include <Application.h>
#include <SupportDefs.h>
#include <AboutWindow.h>
#include <Catalog.h>
#include <Alert.h>

//other system includes
#include <iostream>
#include <vector>
#include <string>


//local includes
#include "defs.h"
#include "mainwindow.h"
#include "inputwindow.h"
#include "settingswindow.h"
#include "gamecontroller.h"


#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "App"


class App : public BApplication
{

	public:
		App(void);
		void MessageReceived(BMessage *msg);
		void AboutRequested();
		bool QuitRequested();
		void ReadyToRun();
		void Pulse();
		
	private:
		
		//windows
		MainWindow *main_window;
		InputWindow *input_window;

		//other properties
		GameController *game_controller;

		//methods
		void start_game();
		void end_game();

};


#endif

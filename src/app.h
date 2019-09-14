/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */
 
#ifndef APP_H
#define APP_H


#include <Application.h>
#include <SimpleGameSound.h>
#include <Path.h>
#include <string>

#include "mainwindow.h"
#include "inputwindow.h"
#include "timerwindow.h"
#include "settingswindow.h"
#include "gamecontroller.h"




enum
{
	ENDGAME_REASON_TIMEOVER=0,
	ENDGAME_REASON_GIVENUP	
};	


class App : public BApplication {
public:
	App();
	~App();
	void MessageReceived(BMessage *msg);
	void AboutRequested();
	bool QuitRequested();
	void ReadyToRun();
	void Pulse();
		
private:
	
	void start_game();
	void end_game(int reason);
	void get_data_dir(BPath &data_path);
	void get_settings_dir(BPath &config_path);
	
	MainWindow	*fMainWindow;
	InputWindow	*fInputWindow;
	TimerWindow	*fTimerWindow;
	
	GameController 		*fGameController;
	BSimpleGameSound	*fGameSound;
	std::string 		fDataDirectory;
	std::string 		fSettingsDirectory;
		
};


#endif

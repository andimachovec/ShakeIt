#ifndef APP_H
#define APP_H


#include <Application.h>
#include <SimpleGameSound.h>

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <array>

#include "defs.h"
#include "mainwindow.h"
#include "inputwindow.h"
#include "timerwindow.h"
#include "settingswindow.h"
#include "gamecontroller.h"
#include "configparser.h"
#include "timerview.h"



enum
{
	ENDGAME_REASON_TIMEOVER=0,
	ENDGAME_REASON_GIVENUP	
};	


class App : public BApplication {
public:
	App();
	void MessageReceived(BMessage *msg);
	void AboutRequested();
	bool QuitRequested();
	void ReadyToRun();
	void Pulse();
		
private:
	
	void start_game();
	void end_game(int reason);
	
	MainWindow	*fMainWindow;
	InputWindow	*fInputWindow;
	TimerWindow	*fTimerWindow;
	
	GameController 		*fGameController;
	BSimpleGameSound	*fGameSound;
	std::string 		fDataDirectory;
		
};


#endif

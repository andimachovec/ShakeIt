/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */
 
#ifndef TIMERWINDOW_H
#define TIMERWINDOW_H


#include <Window.h>
#include <String.h>

#include "timerview.h"


enum
{
	TW_TIMER_UPDATE='tw00',
	TW_TIMER_START,
	TW_TIMER_STOP,

};



class TimerWindow : public BWindow{
public:
	TimerWindow(BString title, BRect frame);
	void MessageReceived(BMessage *msg);
	
	
	
private:


	TimerView *fTimerView;




};

#endif

/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#include "timerwindow.h"

#include <LayoutBuilder.h>
#include <iostream>

TimerWindow::TimerWindow(BString title, BRect frame)
	:
	BWindow(frame, title.String(), B_TITLED_WINDOW,
		B_ASYNCHRONOUS_CONTROLS|
		B_NOT_CLOSABLE|
		B_NOT_H_RESIZABLE|
		B_NOT_V_RESIZABLE|
		B_AVOID_FOCUS)
{

	fTimerView = new TimerView();

	BLayoutBuilder::Group<>(this, B_VERTICAL,0)
		.SetInsets(0)
		.Add(fTimerView)
	.Layout();

}


void
TimerWindow::MessageReceived(BMessage *msg)
{

	switch (msg->what)
	{
		case TW_TIMER_UPDATE:
			fTimerView->UpdateTimer();
			break;

		case TW_TIMER_START:
			fTimerView->StartTimer();
			break;

		case TW_TIMER_STOP:
			fTimerView->StopTimer();
			break;

		default:
			BWindow::MessageReceived(msg);
			break;
	}

}

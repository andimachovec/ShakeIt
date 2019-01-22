#include "timerwindow.h"

#include <LayoutBuilder.h>
#include <iostream>

TimerWindow::TimerWindow(std::string title, BRect frame)
	:
	BWindow(frame, title.c_str(), B_TITLED_WINDOW, 
		B_ASYNCHRONOUS_CONTROLS|B_NOT_CLOSABLE)
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
#include "timerwindow.h"


TimerWindow::TimerWindow(std::string title, BRect frame)
	:
	BWindow(frame, title.c_str(), B_TITLED_WINDOW, 
		B_ASYNCHRONOUS_CONTROLS|B_NOT_CLOSABLE)
{

}


void
TimerWindow::MessageReceived(BMessage *msg)
{

	switch (msg->what)
	{

		

		default:
			BWindow::MessageReceived(msg);
			break;

	}

}
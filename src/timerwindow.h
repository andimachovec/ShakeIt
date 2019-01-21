#ifndef TIMERWINDOW_H
#define TIMERWINDOW_H

#include <Window.h>
#include <string>

class TimerWindow : public BWindow{
public:
	TimerWindow(std::string title, BRect frame);
	void MessageReceived(BMessage *msg);
	
	
	
private:

};

#endif

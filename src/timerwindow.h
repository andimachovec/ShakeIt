#ifndef TIMERWINDOW_H
#define TIMERWINDOW_H


#include <Window.h>
#include <string>


enum
{
	TW_TIMER_UPDATE='tw00',
	TW_TIMER_START,
	TW_TIMER_STOP,

};



class TimerWindow : public BWindow{
public:
	TimerWindow(std::string title, BRect frame);
	void MessageReceived(BMessage *msg);
	
	
	
private:

};

#endif

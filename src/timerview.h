#ifndef TIMERVIEW_H
#define TIMERVIEW_H


#include <TextView.h>
#include <String.h>


enum
{
	TV_TIME_OVER='tv00',

};


class TimerView : public BTextView {
public:
	
	TimerView();
	void StartTimer();
	void StopTimer();
	void UpdateTimer();
	
private:
		
	void time_over();
	void update_display();
	
	bool fIsRunning;
	bigtime_t fStartTime;
	bigtime_t fElapsedTimeSeconds;
		
	int fMinutesToGo;
	int fSecondsToGo;

};


#endif

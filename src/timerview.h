#ifndef TIMERVIEW_H
#define TIMERVIEW_H

#include <TextView.h>
#include <String.h>
#include <Application.h>


enum
{
	TV_TIME_OVER='tv00',

};

#include <iostream>


class TimerView : public BTextView
{

	public:
		TimerView();
		void StartTimer();
		void StopTimer();
		void UpdateTimer();
	
	private:
		
		void time_over();
		void update_display();
		
		bool is_running;
		bigtime_t start_time;
		bigtime_t elapsed_time_seconds;
		bigtime_t elapsed_time_seconds_before;
		
		int minutes_to_go;
		int seconds_to_go;

};

#endif

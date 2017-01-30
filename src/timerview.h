#ifndef TIMERVIEW_H
#define TIMERVIEW_H

#include <View.h>


#include <iostream>


class TimerView : public BView
{

	public:
		TimerView();
		void StartTimer();
		void StopTimer();
		void Pulse();

	private:
		
		bool is_running;
		


};

#endif

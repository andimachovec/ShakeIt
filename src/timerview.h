/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */
 
#ifndef TIMERVIEW_H
#define TIMERVIEW_H


#include <View.h>

enum
{
	TV_TIME_OVER='tv00'
};


class TimerView : public BView {
public:
	
	TimerView();
	void Draw(BRect update_rect);
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

	float fTextHeight;
	float fTextWidth;
};


#endif

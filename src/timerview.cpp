/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */
 
#include "timerview.h"

#include <Application.h>
#include <String.h>


TimerView::TimerView()
		:
		BView("timerview", B_SUPPORTS_LAYOUT|B_WILL_DRAW)
{

	fIsRunning=false;
	
	SetDrawingMode(B_OP_COPY);
	
	BFont clock_font(be_fixed_font);
	clock_font.SetSize(28.0);
	SetFont(&clock_font);

	struct font_height clock_font_height;
	clock_font.GetHeight(&clock_font_height);
	fTextHeight=clock_font_height.ascent;
	fTextWidth=clock_font.StringWidth("00:00");

	SetHighColor(255,0,0);
	SetLowColor(0,0,0);
	SetViewColor(0,0,0);

}


void
TimerView::Draw(BRect update_rect)
{

	if (fIsRunning)
	{
		update_display();
	}

}


void
TimerView::StartTimer()
{
	fIsRunning=true;
	fStartTime=system_time();
}


void
TimerView::StopTimer()
{
	fIsRunning=false;
	
}


void
TimerView::UpdateTimer()
{

	if(fIsRunning)
	{	
	
		fElapsedTimeSeconds=(system_time()-fStartTime)/1000/1000;
		
		if (fElapsedTimeSeconds < 180)
		{
			update_display();	
		}
		
		else
		{
			time_over();	
		}	

	}
}	


void
TimerView::time_over()
{
	fIsRunning=false;
	
	fElapsedTimeSeconds=180;
	update_display();
	
	BMessage *time_over_message = new BMessage(TV_TIME_OVER);
	be_app->PostMessage(time_over_message);
	

}


void
TimerView::update_display()
{

	int fMinutesToGo=(180-fElapsedTimeSeconds) / 60;
	int fSecondsToGo=(180-fElapsedTimeSeconds) % 60; 
	
	BString output_string;
	output_string.SetToFormat("%02d:%02d",fMinutesToGo,fSecondsToGo);
	
	BPoint TextAnchor;
	TextAnchor.x = (Bounds().Width()-fTextWidth) / 2;
	TextAnchor.y = ((Bounds().Height()-fTextHeight) / 2) + fTextHeight;
	FillRect(Bounds(),B_SOLID_LOW);
	DrawString(output_string.String(), TextAnchor);

}


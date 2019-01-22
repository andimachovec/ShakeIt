#include "timerview.h"

#include <Application.h>
#include <String.h>

TimerView::TimerView()
		:
		BView("timerview", B_SUPPORTS_LAYOUT|B_WILL_DRAW)
{

	fIsRunning=false;
	
	BFont clock_font(be_plain_font);
	clock_font.SetSize(28.0);
	SetFont(&clock_font);

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
	
	FillRect(Bounds(),B_SOLID_LOW);
	DrawString(output_string.String(), BPoint(80,60));

}


#include "timerview.h"

#include <Application.h>
#include <iostream>


TimerView::TimerView()
		:
		BTextView("timerview")
{
	fIsRunning=false;

	MakeEditable(false);
	MakeSelectable(false);

	SetAlignment(B_ALIGN_RIGHT);



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
	
	Delete(0,TextLength());
	Insert(output_string);
	
}


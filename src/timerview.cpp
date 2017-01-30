#include "timerview.h"

//-----------------------------------------------------------------------------
TimerView::TimerView()
		: BTextView("timerview")
//-----------------------------------------------------------------------------
{
	is_running=false;

	MakeEditable(false);
	MakeSelectable(false);

	SetAlignment(B_ALIGN_RIGHT);



}



//-----------------------------------------------------------------------------
void TimerView::StartTimer()
//-----------------------------------------------------------------------------
{
	is_running=true;
	start_time=system_time();
}



//-----------------------------------------------------------------------------
void TimerView::StopTimer()
//-----------------------------------------------------------------------------
{
	is_running=false;
	
}



//-----------------------------------------------------------------------------
void TimerView::Pulse()
//-----------------------------------------------------------------------------
{

	if(is_running)
	{	
	
		elapsed_time_seconds=(system_time()-start_time)/1000/1000;
		
		if (elapsed_time_seconds < 180)
		{
			update_display();	
		}
		
		else
		{
			time_over();	
		}	

	}
}	



//-----------------------------------------------------------------------------
void TimerView::time_over()
//-----------------------------------------------------------------------------
{
	is_running=false;
	
	elapsed_time_seconds=180;
	update_display();
	
	BMessage *time_over_message = new BMessage(TV_TIME_OVER);
	be_app->PostMessage(time_over_message);
	

}



//-----------------------------------------------------------------------------
void TimerView::update_display()
//-----------------------------------------------------------------------------
{
	
	int minutes_to_go=(180-elapsed_time_seconds) / 60;
	int seconds_to_go=(180-elapsed_time_seconds) % 60; 
	
	BString output_string;
	output_string.SetToFormat("%02d:%02d",minutes_to_go,seconds_to_go);
	
	Delete(0,TextLength());
	Insert(output_string);
	
}



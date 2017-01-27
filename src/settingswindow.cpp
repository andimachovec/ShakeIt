#include "settingswindow.h"


//-----------------------------------------------------------------------------
SettingsWindow::SettingsWindow()
		: BWindow(BRect(100,100,400,200),"Settings", B_MODAL_WINDOW, B_ASYNCHRONOUS_CONTROLS)
//-----------------------------------------------------------------------------
{
	
	
	save_button = new BButton("Save", new BMessage(SW_SAVE_BUTTON));
	cancel_button = new BButton("Cancel", new BMessage(SW_CANCEL_BUTTON));
	dictionary_textcontrol = new BTextControl("Dictionary file","dictionary.txt",new BMessage(SW_DICTIONARY_TEXT));
	minwordlength_textcontrol = new BTextControl("Minimum word length","4",new BMessage(SW_MINWORDLENGTH_TEXT));
	
	 
	
	BLayoutBuilder::Group<>(this, B_VERTICAL,0)
		.SetInsets(0)
		.Add(dictionary_textcontrol)
		.Add(minwordlength_textcontrol)
		.AddGroup(B_HORIZONTAL)
			.Add(cancel_button)
			.Add(save_button)
		.End()	
	.Layout();	
	
	
}	


//-----------------------------------------------------------------------------
void SettingsWindow::MessageReceived(BMessage *msg)
//-----------------------------------------------------------------------------
{
	switch (msg->what)
	{	
	
	
		case SW_SAVE_BUTTON:
		{
			
			this->Quit();
			break;
			
		}
	
	
		case SW_CANCEL_BUTTON:
		{
			
			this->Quit();
			break;
		}
	
		default:
		{
			BWindow::MessageReceived(msg);
			break;
		}
	
	}
	
}	

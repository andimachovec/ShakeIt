#include "settingswindow.h"


#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "SettingsWindow"


//-----------------------------------------------------------------------------
SettingsWindow::SettingsWindow()
		: BWindow(BRect(100,100,400,200),B_TRANSLATE("Settings"), B_MODAL_WINDOW, B_ASYNCHRONOUS_CONTROLS)
//-----------------------------------------------------------------------------
{
	
	
	save_button = new BButton(B_TRANSLATE("Save"), new BMessage(SW_SAVE_BUTTON));
	cancel_button = new BButton(B_TRANSLATE("Cancel"), new BMessage(SW_CANCEL_BUTTON));
	dictionary_textcontrol = new BTextControl(B_TRANSLATE("Dictionary file"),"dictionary.txt",new BMessage(SW_DICTIONARY_TEXT));
	minwordlength_textcontrol = new BTextControl(B_TRANSLATE("Minimum word length"),"4",new BMessage(SW_MINWORDLENGTH_TEXT));
	
	 
	
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

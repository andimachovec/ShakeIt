#include "settingswindow.h"


#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "SettingsWindow"


//-----------------------------------------------------------------------------
SettingsWindow::SettingsWindow(std::string DictionaryFile, std::string MinimumWordLength)
		: BWindow(BRect(100,100,400,200),B_TRANSLATE("Settings"), B_MODAL_WINDOW, B_ASYNCHRONOUS_CONTROLS), 
		dictionary_file_default(DictionaryFile.c_str()), minimum_word_length_default(MinimumWordLength.c_str())
//-----------------------------------------------------------------------------
{
	
	
	save_button = new BButton(B_TRANSLATE("Save"), new BMessage(SW_BUTTON_SAVE_CLICKED));
	cancel_button = new BButton(B_TRANSLATE("Cancel"), new BMessage(SW_BUTTON_CANCEL_CLICKED));
	dictionary_textcontrol = new BTextControl(B_TRANSLATE("Dictionary file"),dictionary_file_default,new BMessage(SW_TEXT_DICTIONARY_ENTERED));
	minwordlength_textcontrol = new BTextControl(B_TRANSLATE("Minimum word length"),minimum_word_length_default,new BMessage(SW_TEXT_MINWORDLENGTH_ENTERED));
	
	 
	
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
	
	
		case SW_BUTTON_SAVE_CLICKED:
		{
			
			BMessage *save_settings_msg = new BMessage(SW_SETTINGS_SAVE);
			
			if (dictionary_textcontrol->Text() != dictionary_file_default)
			{
				save_settings_msg->AddString("dictionaryfile",dictionary_textcontrol->Text());
			}
			
			if (minwordlength_textcontrol->Text() != minimum_word_length_default)
			{
				save_settings_msg->AddString("minimumwordlength",minwordlength_textcontrol->Text());
			}		
			
			be_app->PostMessage(save_settings_msg);
			
			this->Quit();
			break;
			
		}
	
	
		case SW_BUTTON_CANCEL_CLICKED:
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

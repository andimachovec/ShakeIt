#include "settingswindow.h"

#include <FilePanel.h>
#include <iostream>

#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "SettingsWindow"


//-----------------------------------------------------------------------------
SettingsWindow::SettingsWindow(std::string DictionaryFile, std::string MinimumWordLength)
		: BWindow(BRect(100,100,400,200),B_TRANSLATE("Settings"), B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS), 
		dictionary_file_default(DictionaryFile), minimum_word_length_default(std::stoi(MinimumWordLength))
//-----------------------------------------------------------------------------
{
	
	
	
	save_button = new BButton(B_TRANSLATE("Save"), new BMessage(SW_BUTTON_SAVE_CLICKED));
	cancel_button = new BButton(B_TRANSLATE("Cancel"), new BMessage(SW_BUTTON_CANCEL_CLICKED));
	dictionary_textcontrol = new BTextControl(B_TRANSLATE("Dictionary file"),dictionary_file_default.c_str(),new BMessage(SW_TEXT_DICTIONARY_ENTERED));
	
	choose_dictionary_button = new BButton(B_TRANSLATE("Choose"), new BMessage(SW_BUTTON_CHOOSEDICTIONARY_CLICKED));
	
	minwordlength_spinner = new BSpinner("minwordlengthspinner", B_TRANSLATE("Minimum word length"), new BMessage());
	minwordlength_spinner->SetRange(3,7);
	minwordlength_spinner->SetValue(minimum_word_length_default);
	
	 
	
	BLayoutBuilder::Group<>(this, B_VERTICAL,0)
		.SetInsets(0)
		.AddGroup(B_HORIZONTAL)
			.Add(dictionary_textcontrol)
			.Add(choose_dictionary_button)
		.End()	
		.Add(minwordlength_spinner)
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
			
			if (minwordlength_spinner->Value() != minimum_word_length_default)
			{
				save_settings_msg->AddInt8("minimumwordlength",minwordlength_spinner->Value());
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
	
	
		case SW_BUTTON_CHOOSEDICTIONARY_CLICKED:
		{
			
			
			BFilePanel *dictionary_filepanel = new BFilePanel(B_OPEN_PANEL);
			dictionary_filepanel->SetTarget(this);
			dictionary_filepanel->Show();	
			break;
		}	
	
		case B_REFS_RECEIVED:
		{	
			
			std::cout << "File opened: " << std::endl;
			break;
		}
	
		default:
		{
			BWindow::MessageReceived(msg);
			break;
		}
	
	}
	
}	

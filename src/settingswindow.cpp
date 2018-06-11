#include "settingswindow.h"
#include "configparser.h"

#include <FilePanel.h>
#include <fstream>
#include <iostream>
#include <boost/filesystem.hpp>


#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "SettingsWindow"


//-----------------------------------------------------------------------------
SettingsWindow::SettingsWindow()
		: BWindow(BRect(100,100,400,240),B_TRANSLATE("Settings"), B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS)
//-----------------------------------------------------------------------------
{
	
	language_default=ConfigParser::Config().GetParameter("game_language");
	minimum_word_length_default=std::stoi(ConfigParser::Config().GetParameter("minimum_word_length"));
	
	if (ConfigParser::Config().GetParameter("sound") == "on")
	{
		sound_default=B_CONTROL_ON;		
	}	
	else
	{
		sound_default=B_CONTROL_OFF;	
	}	
	
	
	save_button = new BButton(B_TRANSLATE("Save"), new BMessage(SW_BUTTON_SAVE_CLICKED));
	cancel_button = new BButton(B_TRANSLATE("Cancel"), new BMessage(SW_BUTTON_CANCEL_CLICKED));
	
	sound_checkbox = new BCheckBox("soundcheckbox", B_TRANSLATE("Sound"), new BMessage());
	sound_checkbox->SetValue(sound_default);	
	
	
	language_selector_menu_popup = new BPopUpMenu("languageselectormenu");
	load_language_choices();
	std::map<std::string,std::string>::iterator language_iter; 
	
	//populate languages dropdown menu
	for (language_iter=available_languages.begin(); language_iter!=available_languages.end(); ++language_iter)
	{
		
		BMenuItem *new_menuitem = new BMenuItem(language_iter->second.c_str(), new BMessage());
		language_selector_menu_popup->AddItem(new_menuitem);	
		if (language_iter->first == language_default)
		{
			new_menuitem->SetMarked(true);	
		}	
	
	} 
	//language_selector_menu_popup->ItemAt(0)->SetMarked(true);
	language_selector_menu_field = new BMenuField(B_TRANSLATE("Language"), language_selector_menu_popup);
	
	minwordlength_spinner = new BSpinner("minwordlengthspinner", B_TRANSLATE("Minimum word length"), new BMessage());
	minwordlength_spinner->SetRange(3,7);
	minwordlength_spinner->SetValue(minimum_word_length_default);
	
	 
	BLayoutBuilder::Group<>(this, B_VERTICAL,0)
		.SetInsets(5)
		.AddGroup(B_HORIZONTAL)
			.Add(language_selector_menu_field)
		.End()	
		.Add(minwordlength_spinner)
		.Add(sound_checkbox)
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
			
			/*if (dictionary_textcontrol->Text() != dictionary_file_default)
			{
				save_settings_msg->AddString("dictionaryfile",dictionary_textcontrol->Text());
			}
			*/
			
			if (minwordlength_spinner->Value() != minimum_word_length_default)
			{
				save_settings_msg->AddInt8("minimumwordlength",minwordlength_spinner->Value());
			}		
			
			
			if (sound_checkbox->Value() != sound_default)
			{
				if (sound_checkbox->Value() == B_CONTROL_ON)
				{
					save_settings_msg->AddBool("sound", true);
				}
				else 
				{
					save_settings_msg->AddBool("sound", false);
				}
				
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


//-----------------------------------------------------------------------------
void SettingsWindow::load_language_choices()
//-----------------------------------------------------------------------------
{

	std::string language_directory="/boot/home/config/settings/Boggle/languages";
	boost::filesystem::path language_dir_path(language_directory);	

	boost::filesystem::directory_iterator end_iter;

	for (boost::filesystem::directory_iterator dir_iter(language_dir_path); dir_iter!=end_iter; ++dir_iter)
	{

		if (boost::filesystem::is_directory(dir_iter->path()))
		{
			
			std::ifstream language_desc_file;
			std::string language_code=dir_iter->path().filename().string();			

			language_desc_file.open(dir_iter->path().string()+"/"+language_code+".desc");

			std::string language_description;
			getline(language_desc_file,language_description);
			available_languages.emplace(language_code,language_description);
									
			language_desc_file.close();

		}

	}
	
}


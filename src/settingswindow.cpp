#include "settingswindow.h"
#include "configparser.h"

#include <LayoutBuilder.h>
#include <Layout.h>
#include <LayoutItem.h>
#include <Catalog.h>
#include <FilePanel.h>
#include <Application.h>
#include <Catalog.h>

#include <fstream>
#include <iostream>
#include <boost/filesystem.hpp>
#include <cstring>

#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "SettingsWindow"


SettingsWindow::SettingsWindow()
		: 
		BWindow(BRect(100,100,400,240),B_TRANSLATE("Settings"), B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS)
{
	
	fLanguageDefault=ConfigParser::Config().GetParameter("game_language");
	fMinWordLengthDefault=std::stoi(ConfigParser::Config().GetParameter("minimum_word_length"));
	
	if (ConfigParser::Config().GetParameter("sound") == "on")
	{
		fSoundDefault=B_CONTROL_ON;		
	}	
	else
	{
		fSoundDefault=B_CONTROL_OFF;	
	}	
	
	
	fSaveButton = new BButton(B_TRANSLATE("Save"), new BMessage(SW_BUTTON_SAVE_CLICKED));
	fCancelButton = new BButton(B_TRANSLATE("Cancel"), new BMessage(SW_BUTTON_CANCEL_CLICKED));
	
	fSoundCheckbox = new BCheckBox("soundcheckbox", B_TRANSLATE("Sound"), new BMessage());
	fSoundCheckbox->SetValue(fSoundDefault);	
	
	
	fLanguageSelectorMenuPopup = new BPopUpMenu("languageselectormenu");
	load_language_choices();
	std::vector<std::pair<std::string,std::string>>::iterator language_iter; 
	
	//populate languages dropdown menu
	for (language_iter=fAvailableLanguages.begin(); language_iter!=fAvailableLanguages.end(); ++language_iter)
	{
		
		BMenuItem *new_menuitem = new BMenuItem(language_iter->second.c_str(), new BMessage());
		fLanguageSelectorMenuPopup->AddItem(new_menuitem);	
		if (language_iter->first == fLanguageDefault)
		{
			new_menuitem->SetMarked(true);	
			fLanguageDefaultDescription=language_iter->second.c_str();
		}	
	
	} 
	//fLanguageSelectorMenuPopup->ItemAt(0)->SetMarked(true);
	fLanguageSelectorMenuField = new BMenuField(B_TRANSLATE("Language"), fLanguageSelectorMenuPopup);
	
	fMinWordLengthSpinner = new BSpinner("minwordlengthspinner", B_TRANSLATE("Minimum word length"), new BMessage());
	fMinWordLengthSpinner->SetRange(3,7);
	fMinWordLengthSpinner->SetValue(fMinWordLengthDefault);
	
	 
	BLayoutBuilder::Group<>(this, B_VERTICAL,0)
		.SetInsets(5)
		.AddGroup(B_HORIZONTAL)
			.Add(fLanguageSelectorMenuField)
		.End()	
		.Add(fMinWordLengthSpinner)
		.Add(fSoundCheckbox)
		.AddGroup(B_HORIZONTAL)
			.Add(fCancelButton)
			.Add(fSaveButton)
		.End()	
	.Layout();	
	
	
}	


void
SettingsWindow::MessageReceived(BMessage *msg)
{
	switch (msg->what)
	{	
	
	
		case SW_BUTTON_SAVE_CLICKED:
		{
			
			BMessage *save_settings_msg = new BMessage(SW_SETTINGS_SAVE);		
			
			if (strcmp(fLanguageSelectorMenuPopup->FindMarked()->Label(), fLanguageDefaultDescription))
			{
				
				int selected_language_index=fLanguageSelectorMenuPopup->FindMarkedIndex();
				save_settings_msg->AddString("gamelanguage",fAvailableLanguages[selected_language_index].first.c_str());
		
			}
			
			
			if (fMinWordLengthSpinner->Value() != fMinWordLengthDefault)
			{
				save_settings_msg->AddInt8("minimumwordlength",fMinWordLengthSpinner->Value());
			}		
			
			
			if (fSoundCheckbox->Value() != fSoundDefault)
			{
				if (fSoundCheckbox->Value() == B_CONTROL_ON)
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


void
SettingsWindow::load_language_choices()
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
			fAvailableLanguages.push_back(std::make_pair(language_code,language_description));
									
			language_desc_file.close();

		}

	}
	
}


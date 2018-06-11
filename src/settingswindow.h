#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <Window.h>
#include <TextControl.h>
#include <Button.h>
#include <LayoutBuilder.h>
#include <Layout.h>
#include <LayoutItem.h>
#include <Catalog.h>
#include <Application.h>
#include <Spinner.h>
#include <PopUpMenu.h>
#include <MenuField.h>
#include <CheckBox.h>

#include <string>
#include <map>


enum
{
	SW_BUTTON_SAVE_CLICKED='sw00',
	SW_BUTTON_CANCEL_CLICKED,
	SW_BUTTON_CHOOSEDICTIONARY_CLICKED,
	SW_TEXT_DICTIONARY_ENTERED,	
	SW_DICTFILE_SELECTED,
	SW_SETTINGS_SAVE,
};	



class SettingsWindow : public BWindow
{
	
	public:
		SettingsWindow();
		void MessageReceived(BMessage *msg);
	
	private:
		
		void load_language_choices();
		
		
		BButton *save_button;
		BButton *cancel_button;
		BPopUpMenu	*language_selector_menu_popup; 
		BMenuField 	*language_selector_menu_field;
		BCheckBox	*sound_checkbox;
		BSpinner *minwordlength_spinner;
		
		std::string language_default;
		int minimum_word_length_default;
		int32 sound_default;
		std::map<std::string, std::string> available_languages;

};	



#endif

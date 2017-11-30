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


#include <string>

enum
{
	SW_BUTTON_SAVE_CLICKED='sw00',
	SW_BUTTON_CANCEL_CLICKED,
	SW_BUTTON_CHOOSEDICTIONARY_CLICKED,
	SW_TEXT_DICTIONARY_ENTERED,	
	SW_SETTINGS_SAVE,
};	



class SettingsWindow : public BWindow
{
	
	public:
		SettingsWindow(std::string DictionaryFile, std::string MinimumWordLength);
		void MessageReceived(BMessage *msg);
	
	private:
		BButton *save_button;
		BButton *cancel_button;
		BTextControl *dictionary_textcontrol;
		BButton *choose_dictionary_button;
		BSpinner *minwordlength_spinner;
		
		std::string dictionary_file_default;
		int minimum_word_length_default;
		

};	



#endif

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

#include <string>

enum
{
	SW_BUTTON_SAVE_CLICKED='sw00',
	SW_BUTTON_CANCEL_CLICKED,
	SW_TEXT_DICTIONARY_ENTERED,
	SW_TEXT_MINWORDLENGTH_ENTERED,	
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
		BTextControl *minwordlength_textcontrol;

		const char* dictionary_file_default;
		const char* minimum_word_length_default;
		

};	



#endif

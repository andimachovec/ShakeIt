#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <Window.h>
#include <TextControl.h>
#include <Button.h>
#include <LayoutBuilder.h>
#include <Layout.h>
#include <LayoutItem.h>
#include <Catalog.h>


enum
{
	SW_SAVE_BUTTON='sw00',
	SW_CANCEL_BUTTON,
	SW_DICTIONARY_TEXT,
	SW_MINWORDLENGTH_TEXT,	
};	



class SettingsWindow : public BWindow
{
	
	public:
		SettingsWindow();
		void MessageReceived(BMessage *msg);
	
	private:
		BButton *save_button;
		BButton *cancel_button;
		BTextControl *dictionary_textcontrol;
		BTextControl *minwordlength_textcontrol;

};	



#endif

/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <Window.h>
#include <TextControl.h>
#include <Button.h>
#include <Spinner.h>
#include <PopUpMenu.h>
#include <MenuField.h>
#include <CheckBox.h>
#include <Path.h>

#include <string>
#include <utility>
#include <vector>

enum
{
	SW_BUTTON_SAVE_CLICKED='sw00',
	SW_BUTTON_CANCEL_CLICKED,
	SW_BUTTON_CHOOSEDICTIONARY_CLICKED,
	SW_TEXT_DICTIONARY_ENTERED,
	SW_DICTFILE_SELECTED,
	SW_SETTINGS_SAVE,
};


class SettingsWindow : public BWindow {
public:

	SettingsWindow(BPath data_path);
	void MessageReceived(BMessage *msg);

private:

	void load_language_choices();

	BButton *fSaveButton;
	BButton *fCancelButton;
	BPopUpMenu	*fLanguageSelectorMenuPopup;
	BMenuField 	*fLanguageSelectorMenuField;
	BCheckBox	*fSoundCheckbox;
	BSpinner *fMinWordLengthSpinner;

	std::string fLanguageDefault;
	const char *fLanguageDefaultDescription;
	int fMinWordLengthDefault;
	int32 fSoundDefault;
	std::vector<std::pair<std::string, std::string>> fAvailableLanguages;
	BPath fDataPath;

};


#endif

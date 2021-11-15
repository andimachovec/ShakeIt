/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#include "statusview.h"
#include "configparser.h"

#include <Catalog.h>
#include <Resources.h>
#include <Application.h>

#include <fstream>
#include <string>


#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "StatusView"


StatusView::StatusView(BPath data_path)
	:
	BStringView("statusview",""),
	fDataDirectory(data_path.Path())

{

	UpdateStatus();
}


void
StatusView::UpdateStatus()
{

		//get game settings from config parser
		BString game_language = ConfigParser::Config().GetGameLanguage();
		uint8 minimum_word_length = ConfigParser::Config().GetMinWordLength();
		bool sound = ConfigParser::Config().GetSound();

		//fetch language description from config dir
		BString language_desc_filename;
		language_desc_filename << fDataDirectory << "/languages/" << game_language << "/" << game_language << ".desc";
		std::ifstream language_desc_file;
		language_desc_file.open(language_desc_filename.String());

		std::string language_description;
		getline(language_desc_file,language_description);

		language_desc_file.close();


		//set sound status (for translation)
		BString sound_status;
		if (sound == true)
		{
			sound_status = B_TRANSLATE("on");
		}
		else
		{
			sound_status = B_TRANSLATE("off");
		}

		//build status message and display it
		BString status_message;
		status_message << "  " <<
				B_TRANSLATE("Game language") << ": " << language_description.c_str() << "     " <<
				B_TRANSLATE("Minimum word length") << ": " << minimum_word_length << "     " <<
				B_TRANSLATE("Sound") << ": " << sound_status;

		SetText(status_message.String());

}

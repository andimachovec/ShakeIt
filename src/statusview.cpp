/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#include "statusview.h"
#include "configparser.h"
#include "datainterface.h"

#include <Catalog.h>
#include <Resources.h>
#include <Application.h>

#include <string>


#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "StatusView"


StatusView::StatusView()
	:
	BStringView("statusview","")
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
				B_TRANSLATE("Game language") << ": " << DataInterface::Data().GetLanguageDescription(game_language) << "     " <<
				B_TRANSLATE("Minimum word length") << ": " << minimum_word_length << "     " <<
				B_TRANSLATE("Sound") << ": " << sound_status;

		SetText(status_message.String());

}

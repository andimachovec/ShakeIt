#include "statusview.h"
#include "configparser.h"

#include <Catalog.h>
#include <Resources.h>
#include <Application.h>

#include <sstream>
#include <fstream>


#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "StatusView"


StatusView::StatusView()
	:
	BStringView("statusview","")

{
	
	BResources *res = be_app->AppResources();
	size_t size;
	
	fDataDirectory=std::string((const char*) res->LoadResource(B_STRING_TYPE,"DataDirectory", &size));
	
	
	UpdateStatus();

}


void
StatusView::UpdateStatus()
{

		//get game settings from config parser
		std::string game_language = ConfigParser::Config().GetParameter("game_language");
		std::string minimum_word_length = ConfigParser::Config().GetParameter("minimum_word_length");
		std::string sound = ConfigParser::Config().GetParameter("sound");
		
		//fetch language description from config dir
		std::ifstream language_desc_file;
		language_desc_file.open(fDataDirectory+"/languages/"+game_language+"/"+game_language+".desc");
		
		std::string language_description;
		getline(language_desc_file,language_description);

		language_desc_file.close();

		std::string sound_status;
		//set sound status (for translation)
		if (sound == "on")
		{
			sound_status = (B_TRANSLATE("on"));
		}
		else 
		{
			sound_status = (B_TRANSLATE("off"));
		}
		
		//build status message and display it
		std::stringstream status_message; 		
		status_message << "  " <<
				B_TRANSLATE("Game language") << ": " << language_description << "     " <<
				B_TRANSLATE("Minimum word length") << ": " << minimum_word_length << "     " <<
				B_TRANSLATE("Sound") << ": " << sound_status;
		
		SetText(status_message.str().c_str());
		
}
#include "statusview.h"
#include "configparser.h"
#include "defs.h"

#include <Catalog.h>
#include <string>
#include <sstream>
#include <fstream>


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
		std::string game_language = ConfigParser::Config().GetParameter("game_language");
		std::string minimum_word_length = ConfigParser::Config().GetParameter("minimum_word_length");

		//fetch language description from config dir
		std::ifstream language_desc_file;
		language_desc_file.open(APPDATADIRECTORY"/languages/"+game_language+"/"+game_language+".desc");
		
		std::string language_description;
		getline(language_desc_file,language_description);

		language_desc_file.close();

		
		//build status message and display it
		std::stringstream status_message; 		
		status_message << "  " <<
				B_TRANSLATE("game language") << ": " << language_description << "     " <<
				B_TRANSLATE("minimum word length") <<": " << minimum_word_length;
		
		SetText(status_message.str().c_str());
		
}
#include "statusview.h"
#include "configparser.h"

#include <Catalog.h>
#include <string>
#include <sstream>


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

		std::string game_language = ConfigParser::Config().GetParameter("game_language");
		std::string minimum_word_length = ConfigParser::Config().GetParameter("minimum_word_length");

		
		std::stringstream status_message; 		
		status_message << 
				B_TRANSLATE("game language: ") << game_language << "             " <<
				B_TRANSLATE("minimum word length: ") << minimum_word_length;
		
		SetText(status_message.str().c_str());
		
}
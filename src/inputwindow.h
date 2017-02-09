#ifndef INPUTWINDOW_H
#define INPUTWINDOW_H

#include <Window.h>
#include <TextView.h>
#include <LayoutBuilder.h>
#include <Layout.h>
#include <LayoutItem.h>

#include <string>
#include <vector>
#include <sstream>
#include <boost/algorithm/string/trim.hpp>
#include <array>

#include <iostream>

#include "gamecontroller.h"  //just for the round_results typedef


enum
{
	IW_TEXT_ENABLE_EDIT='iw00',
	IW_TEXT_DISABLE_EDIT,	
	IW_TEXT_CLEAR,
	IW_TEXT_SHOW,
};	



class InputWindow : public BWindow
{
	
	public:
		InputWindow();
		void MessageReceived(BMessage *msg);
		std::vector<std::string> GetWordList();
		//void DisplayResults(round_results results, int points_current_round, std::vector<std::string> missing_words);
	
	private:
		BTextView *words_textview;
		
		std::vector<std::string> word_list;
		std::array<std::string,5> result_text;
		
		
};	



#endif

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
#include <iostream>

#include "gamecontroller.h"  //just for the round_results typedef

class InputWindow : public BWindow
{
	
	public:
		InputWindow();
		void ClearText();
		void SetTextActive();
		void SetTextInactive();
		std::vector<std::string> GetWordList();
		void DisplayResults(round_results results, int points_current_round, std::vector<std::string> missing_words);
	
	private:
		BTextView *words_textview;
		
		std::vector<std::string> word_list;
	
		
		
};	



#endif

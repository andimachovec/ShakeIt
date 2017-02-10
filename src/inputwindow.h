#ifndef INPUTWINDOW_H
#define INPUTWINDOW_H

#include <Window.h>
#include <TextView.h>
#include <LayoutBuilder.h>
#include <Layout.h>
#include <LayoutItem.h>
#include <ScrollBar.h>

#include <string>
#include <vector>
#include <sstream>
#include <boost/algorithm/string/trim.hpp>


#include <iostream>


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
		InputWindow(float left, float top, float right, float bottom);
		void MessageReceived(BMessage *msg);
		std::vector<std::string> GetWordList();
		
	
	private:
		BTextView *words_textview;
		BScrollBar *words_textview_scrollbar;
		
		std::vector<std::string> word_list;
		
};	



#endif

/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */
 
#ifndef INPUTWINDOW_H
#define INPUTWINDOW_H

#include <Window.h>
#include <TextView.h>
#include <ScrollBar.h>

#include <string>
#include <vector>
#include <sstream>


enum
{
	IW_TEXT_ENABLE_EDIT='iw00',
	IW_TEXT_DISABLE_EDIT,	
	IW_TEXT_CLEAR,
	IW_TEXT_SHOW,
	IW_ACTIVATE,
};	



class InputWindow : public BWindow {
public:	
	
	InputWindow(std::string title, BRect frame);
	void MessageReceived(BMessage *msg);
	std::vector<std::string> GetWordList();
	void WindowActivated(bool active);
	
private:
	
	BTextView *fWordsTextview;
	BScrollBar *fWordsTextviewScrollbar;
		
	std::vector<std::string> fWordList;
		
};	



#endif

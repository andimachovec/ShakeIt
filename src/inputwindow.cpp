/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */
 
#include "inputwindow.h"

#include <LayoutBuilder.h>
#include <Layout.h>
#include <LayoutItem.h>
#include <Catalog.h>

#include <boost/algorithm/string/trim.hpp>
#include <iostream>



#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "InputWindow"



InputWindow::InputWindow(std::string title, BRect frame)
		: 
		BWindow(frame, title.c_str(), B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS|B_NOT_CLOSABLE)
{
	
	
	fWordsTextview = new BTextView("wordinput");
	fWordsTextview->SetInsets(8,8,8,8);
	fWordsTextview->SetViewColor(237,227,208);
	fWordsTextviewScrollbar = new BScrollBar("wordscroll",fWordsTextview,1,100,B_VERTICAL);
	
	BLayoutBuilder::Group<>(this, B_VERTICAL,0)
		.SetInsets(0)
		.AddGroup(B_HORIZONTAL)
			.Add(fWordsTextview)
		.End()	
	.Layout();	
	
	
}	


void 
InputWindow::MessageReceived(BMessage *msg)
{
	
	switch (msg->what)	
	{
		
		
		case IW_TEXT_ENABLE_EDIT:
		{
			fWordsTextview->MakeEditable(true);
			break;
		}
		
		case IW_TEXT_DISABLE_EDIT:
		{
			fWordsTextview->MakeEditable(false);
			break;
		}
		
		case IW_TEXT_CLEAR:
		{
			fWordsTextview->SelectAll();
			fWordsTextview->Clear();
			break;
		}
		
		case IW_TEXT_SHOW:
		{ 
			fWordsTextview->SetText(msg->GetString("text"),strlen(msg->GetString("text")));
			break;
		}
		
		case IW_ACTIVATE:
		{
			Activate(true);
			break;
		}
						
		default:
		{
			BWindow::MessageReceived(msg);
			break;
		}
	}

}	


std::vector<std::string>
InputWindow::GetWordList()
{
	
	//empty the word list vector
	fWordList.clear();
	
	//get the words from the textview
	std::string words_text = std::string(fWordsTextview->Text());
	
	//put the text into a stream and parse it into a vector line by line
	std::istringstream wordlist_stream(words_text);
	std::string line;
	
	while (std::getline(wordlist_stream,line))
	{
		//strip leading and trailing whitespace
		boost::algorithm::trim(line);
	
		if (!line.empty())
		{
			fWordList.push_back(line);
			//std::cout << line << std::endl;
		}
		
	}

	
	return fWordList;
}	


void
InputWindow::WindowActivated(bool active)
{

	if (active)
	{
	
		fWordsTextview->MakeFocus(true);

	}
	
}	


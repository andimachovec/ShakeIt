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
#include <StringList.h>

#include <iostream>


#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "InputWindow"


InputWindow::InputWindow(BString title, BRect frame)
		:
		BWindow(frame, title.String(), B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS|B_NOT_CLOSABLE)
{

	fWordsTextview = new BTextView("wordinput");
	fWordsTextview->SetInsets(8,8,8,8);
	fWordsTextview->SetViewColor(237,227,208);
	fWordsTextviewScrollbar = new BScrollBar("wordscroll",fWordsTextview,1,100,B_VERTICAL);

	fWordsTextview->SetText(B_TRANSLATE("Enter your words here, one by line. Case is ignored."));

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

	//parse words into vector line by line
	BString words_text(fWordsTextview->Text());
	BStringList words_list;
	words_text.Split("\n", true, words_list);

	for(int32 index = 0; index < words_list.CountStrings(); ++index)
	{
		fWordList.push_back(std::string(words_list.StringAt(index).Trim().ToUpper().String()));
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

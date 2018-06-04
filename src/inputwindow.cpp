#include "inputwindow.h"


#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "InputWindow"


//-----------------------------------------------------------------------------
InputWindow::InputWindow(std::string title, BRect frame)
		: BWindow(frame, title.c_str(), B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS|B_NOT_CLOSABLE)
//-----------------------------------------------------------------------------
{
	
	
	words_textview = new BTextView("wordinput");
	words_textview_scrollbar = new BScrollBar("wordscroll",words_textview,1,100,B_VERTICAL);
	
	BLayoutBuilder::Group<>(this, B_VERTICAL,0)
		.SetInsets(0)
		.AddGroup(B_HORIZONTAL)
			.Add(words_textview)
		.End()	
	.Layout();	
	
	
}	



//----------------------------------------------------------------------------
void InputWindow::MessageReceived(BMessage *msg)
//----------------------------------------------------------------------------
{
	
	switch (msg->what)	
	{
		
		
		case IW_TEXT_ENABLE_EDIT:
		{
			words_textview->MakeEditable(true);
			break;
		}
		
		case IW_TEXT_DISABLE_EDIT:
		{
			words_textview->MakeEditable(false);
			break;
		}
		
		case IW_TEXT_CLEAR:
		{
			words_textview->SelectAll();
			words_textview->Clear();
			break;
		}
		
		case IW_TEXT_SHOW:
		{ 
			words_textview->SetText(msg->GetString("text"),strlen(msg->GetString("text")));
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



//-----------------------------------------------------------------------------
std::vector<std::string> InputWindow::GetWordList()
//-----------------------------------------------------------------------------
{
	
	//empty the word list vector
	word_list.clear();
	
	//get the words from the textview
	std::string words_text = std::string(words_textview->Text());
	
	//put the text into a stream and parse it into a vector line by line
	std::istringstream wordlist_stream(words_text);
	std::string line;
	
	while (std::getline(wordlist_stream,line))
	{
		//strip leading and trailing whitespace
		boost::algorithm::trim(line);
	
		if (!line.empty())
		{
			word_list.push_back(line);
			//std::cout << line << std::endl;
		}
		
	}

	
	return word_list;
}	



//-----------------------------------------------------------------------------
void InputWindow::WindowActivated(bool active)
//-----------------------------------------------------------------------------
{

	if (active)
	{
	
		words_textview->MakeFocus(true);

	}
	
}	


#include "inputwindow.h"


//-----------------------------------------------------------------------------
InputWindow::InputWindow()
		: BWindow(BRect(100,100,500,400),"Word Input", B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS|B_NOT_CLOSABLE)
//-----------------------------------------------------------------------------
{
	
	
	words_textview = new BTextView("wordinput");
	
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



////-----------------------------------------------------------------------------
//void InputWindow::DisplayResults(round_results results, int points_current_round, std::vector<std::string> missing_words)
////-----------------------------------------------------------------------------
//{
//	
//	std::cout << "-----------------------------------------------------------" << std::endl;
//	std::cout << "InputWindow::DisplayResults starting...." << std::endl;
//	
//	//empty the text view
//	//ClearText();
//	
//	
//	//loop through wordlist and output the words an the status (valid or not, points)
//	
//	std::stringstream result_stream;
//	
//	for (int i=0; i < word_list.size(); ++i)
//	{
//	
//		int result_code = results[i].first;
//		int result_points = results[i].second;
//		
//		
//		
//		if (result_code == 0)  //display the valid word along with the given points
//		{ 
//			
//			result_stream << word_list[i] << " (" << result_points << ")\n";	
//			std::cout << result_stream.str();
//			//words_textview->Insert(result_stream.str().c_str());
//			
//			
//		}
//		else	//display invalid word in red along with the reason why they´re invalid
//		{
//		
//			
//			
//			result_stream << word_list[i] << " (" << result_text[result_code] << ")\n";
//			std::cout << result_stream.str();
//			//words_textview->Insert(result_stream.str().c_str());
//		
//		}
//	
//		result_stream.str("");
//	    result_stream.clear();
//		
//	}
//
//
//	//display total points in this round
//	result_stream.str("");
//	result_stream.clear();
//	result_stream << "\n" << "Points in this round" << ": " << points_current_round << "\n";
//	//words_textview->Insert(result_stream.str().c_str());
//	std::cout << result_stream.str();
//	
//	//if there are words that the player didn´t find, display them
//	if (!missing_words.empty())
//	{
//		result_stream.str("");
//		result_stream.clear();
//		
//		result_stream << "\n\n";
//		result_stream << "Missing words" << ":\n";
//	
//		std::vector<std::string>::iterator mw_iter;
//	
//		for (mw_iter=missing_words.begin();mw_iter!=missing_words.end();++mw_iter)
//		{
//	
//			result_stream << *mw_iter << "\n";
//	
//		}
//		
//		//words_textview->Insert(result_stream.str().c_str());
//		std::cout << result_stream.str();
//	}
//	
//	std::cout << "InputWindow::DisplayResults done...." << std::endl;
//	std::cout << "-----------------------------------------------------------" << std::endl;
//}	

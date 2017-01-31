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


//-----------------------------------------------------------------------------
void InputWindow::ClearText()
//-----------------------------------------------------------------------------
{
	words_textview->SelectAll();
	words_textview->Clear();
	
}	


//-----------------------------------------------------------------------------
void InputWindow::SetTextActive()
//-----------------------------------------------------------------------------
{
	words_textview->MakeEditable(true);
	
}	



//-----------------------------------------------------------------------------
void InputWindow::SetTextInactive()
//-----------------------------------------------------------------------------
{
	words_textview->MakeEditable(false);
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
			std::cout << line << std::endl;
		}
		
	}
	
	return word_list;
}	



//-----------------------------------------------------------------------------
void InputWindow::DisplayResults(round_results results, int points_current_round, std::vector<std::string> missing_words)
//-----------------------------------------------------------------------------
{
	
	//empty the text view
	ClearText();
	
	
	//loop through wordlist and output the words an the status (valid or not, points)
	
	for (int i=0; i < word_list.size(); ++i)
	{
	
		int result_code = results[i].first;
		int result_points = results[i].second;
		
		
		
		if (result_code == 0)  //display the valid word along with the given points
		{ 
			
			//*WordInput << word_list[i] << " (" << result_points << ")\n";	
			words_textview.Insert();
			
			
		}
		else	//display invalid word in red along with the reason why they´re invalid
		{
		
			
			
			//*WordInput << word_list[i] << " (" << result_text[result_code] << ")\n";
			words_textview.Insert()
		
		}
	

		
	}


	//display total points in this round
	*WordInput << "\n" << _("Points in this round") << ": " << points_current_round << "\n";
	
	
//	//if there are words that the player didn´t find, display them
//	if (!missing_words.empty())
//	{
//		
//		*WordInput << "\n\n";
//		*WordInput << _("Missing words") << ":\n";
//	
//		std::vector<std::string>::iterator mw_iter;
//	
//		for (mw_iter=missing_words.begin();mw_iter!=missing_words.end();++mw_iter)
//		{
//	
//			*WordInput << *mw_iter << "\n";
//	
//		}
//
//	}
	
}	

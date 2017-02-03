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
	
	//assign status messages for the word evaluation
	result_text[0]="OK";
	result_text[1]="too short";
	result_text[2]="not possible";
	result_text[3]="not in dictionary";
	result_text[4]="duplicate";

	std::cout << "InputWindow::InputWindow done...." << std::endl;
}	


//-----------------------------------------------------------------------------
void InputWindow::ClearText()
//-----------------------------------------------------------------------------
{
	words_textview->SelectAll();
	words_textview->Clear();
	
	std::cout << "InputWindow::ClearText done...." << std::endl;
}	


//-----------------------------------------------------------------------------
void InputWindow::SetTextActive()
//-----------------------------------------------------------------------------
{
	//words_textview->MakeEditable(true);
	
	std::cout << "InputWindow::SetTextActive done...." << std::endl;
}	



//-----------------------------------------------------------------------------
void InputWindow::SetTextInactive()
//-----------------------------------------------------------------------------
{
	//words_textview->MakeEditable(false);
	
	std::cout << "InputWindow::SetTextInactive done...." << std::endl;

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
	
	
	std::cout << "InputWindow::GetWordList done...." << std::endl;
	
	return word_list;
}	



//-----------------------------------------------------------------------------
void InputWindow::DisplayResults(round_results results, int points_current_round, std::vector<std::string> missing_words)
//-----------------------------------------------------------------------------
{
	
	std::cout << "-----------------------------------------------------------" << std::endl;
	std::cout << "InputWindow::DisplayResults starting...." << std::endl;
	
	//empty the text view
	ClearText();
	
	
	//loop through wordlist and output the words an the status (valid or not, points)
	
	std::stringstream result_stream;
	
	for (int i=0; i < word_list.size(); ++i)
	{
	
		int result_code = results[i].first;
		int result_points = results[i].second;
		
		
		
		if (result_code == 0)  //display the valid word along with the given points
		{ 
			
			result_stream << word_list[i] << " (" << result_points << ")\n";	
			std::cout << result_stream.str();
			//words_textview->Insert(result_stream.str().c_str());
			
			
		}
		else	//display invalid word in red along with the reason why they´re invalid
		{
		
			
			
			result_stream << word_list[i] << " (" << result_text[result_code] << ")\n";
			std::cout << result_stream.str();
			//words_textview->Insert(result_stream.str().c_str());
		
		}
	
		result_stream.str("");
	    result_stream.clear();
		
	}


	//display total points in this round
	result_stream.str("");
	result_stream.clear();
	result_stream << "\n" << "Points in this round" << ": " << points_current_round << "\n";
	//words_textview->Insert(result_stream.str().c_str());
	std::cout << result_stream.str();
	
	//if there are words that the player didn´t find, display them
	if (!missing_words.empty())
	{
		result_stream.str("");
		result_stream.clear();
		
		result_stream << "\n\n";
		result_stream << "Missing words" << ":\n";
	
		std::vector<std::string>::iterator mw_iter;
	
		for (mw_iter=missing_words.begin();mw_iter!=missing_words.end();++mw_iter)
		{
	
			result_stream << *mw_iter << "\n";
	
		}
		
		//words_textview->Insert(result_stream.str().c_str());
		std::cout << result_stream.str();
	}
	
	std::cout << "InputWindow::DisplayResults done...." << std::endl;
	std::cout << "-----------------------------------------------------------" << std::endl;
}	

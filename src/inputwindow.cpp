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
	//words_textview->MakeEditable(true);
	
}	



//-----------------------------------------------------------------------------
void InputWindow::SetTextInactive()
//-----------------------------------------------------------------------------
{
	//words_textview->MakeEditable(false);
}	



//-----------------------------------------------------------------------------
std::vector<std::string> InputWindow::GetWordList()
//-----------------------------------------------------------------------------
{
	std::vector<std::string> wordlist;
	
	
	return wordlist;
}	


//
////-----------------------------------------------------------------------------
//void InputWindow::DisplayResults(round_results results, int points_current_round, std::vector<std::string> missing_words)
////-----------------------------------------------------------------------------
//{
//	
//	
//}	

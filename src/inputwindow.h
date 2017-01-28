#ifndef INPUTWINDOW_H
#define INPUTWINDOW_H

#include <Window.h>
#include <TextView.h>
#include <LayoutBuilder.h>
#include <Layout.h>
#include <LayoutItem.h>

#include <string>
#include <vector>


class InputWindow : public BWindow
{
	
	public:
		InputWindow();
		//void ClearText(void);
		//void SetTextActive(void);
		//void SetTextInactive(void);
		//std::vector<std::string> GetWordList(void);
		//void DisplayResults(round_results results, int points_current_round, std::vector<std::string> missing_words);
	
	private:
		BTextView *words_textview;
		
};	



#endif

#ifndef LETTERVIEW_H
#define LETTERVIEW_H

#include <View.h>
#include <TranslationUtils.h>
#include <TranslatorFormats.h>
#include <Bitmap.h>

#include <string>
#include <vector>


class LetterView : public BView
{

	public:
		LetterView();
		void Draw(BRect update_rect);
		void SetLetters(std::vector<std::string> LetterCombination);
		
		
	private:
		
		
		BBitmap *board_letters[16];		
	
	
		
};	



#endif 

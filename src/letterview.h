#ifndef LETTERVIEW_H
#define LETTERVIEW_H

#include <View.h>
#include <TranslationUtils.h>
#include <TranslatorFormats.h>
#include <Bitmap.h>
#include <Layout.h>
#include <LayoutItem.h>
#include <GridLayout.h>

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

class LetterView : public BView
{

	public:
		LetterView();
		void Draw(BRect update_rect);
		void SetLetters(std::vector<std::string> Letters, std::vector<int> LetterOrientation);
		
		
	private:
			
		void load_bitmaps();
		void draw_bitmaps();
				
		BBitmap *board_letters[16];		
		std::string letter_filenames[16];
	
		
};	



#endif 

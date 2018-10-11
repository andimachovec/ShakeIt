#ifndef LETTERVIEW_H
#define LETTERVIEW_H

#include <View.h>
#include <Bitmap.h>

#include <string>
#include <vector>


class LetterView : public BView {
public:
	
	LetterView();
	void Draw(BRect update_rect);
	void SetLetters(std::vector<std::string> Letters, std::vector<int> LetterOrientation);
		
private:
			
	void load_bitmaps();
	void draw_bitmaps();
				
	BBitmap *fBoardLetters[16];		
	std::string fLetterFilenames[16];
		
};	


#endif 

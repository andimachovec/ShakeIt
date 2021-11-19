/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */
 
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

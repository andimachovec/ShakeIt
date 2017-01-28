#include "letterview.h"


//-----------------------------------------------------------------------------
LetterView::LetterView()
		: BView("letterview", B_SUPPORTS_LAYOUT|B_WILL_DRAW)
//-----------------------------------------------------------------------------
{
		
	for (int i=0; i<16; ++i)
	{
	
		letter_filenames[i]="empty.png";	
		
	}	
	
	load_bitmaps();
	draw_bitmaps();
}	



//-----------------------------------------------------------------------------
void LetterView::Draw(BRect update_rect)
//-----------------------------------------------------------------------------
{
	
	draw_bitmaps();
	
	
}	



//-----------------------------------------------------------------------------
void LetterView::SetLetters(std::vector<std::string> Letters, std::vector<int> LetterOrientation)
//-----------------------------------------------------------------------------
{

	for (int i=0; i<16; ++i)
	{
		
		std::stringstream filename_stream;
		filename_stream << Letters[i] << "-" << LetterOrientation[i] << ".png";
		
		letter_filenames[i]=filename_stream.str();
		
	}	 
	
	load_bitmaps();
	draw_bitmaps();
	
	
}	



//-----------------------------------------------------------------------------
void LetterView::load_bitmaps()
//-----------------------------------------------------------------------------
{

	for (int i=0; i<16; ++i)
	{
		std::string bitmap_name="../"+letter_filenames[i];
		board_letters[i] = BTranslationUtils::GetBitmap(bitmap_name.c_str());		
	}	 

}	



//-----------------------------------------------------------------------------
void LetterView::draw_bitmaps()
//-----------------------------------------------------------------------------
{

	SetDrawingMode(B_OP_ALPHA);
	//SetHighColor(255,255,255);
	//FillRect(Bounds());
	
	
	int x_start=80;
	int y_start=40;
	int x_delta=80;
	int y_delta=80;
	
	int letter_index=0;
	int draw_coord_x=x_start;
	int draw_coord_y=y_start;
	
	
	for (int rows=0; rows<4; ++rows)
	{
		for (int cols=0; cols<4; ++cols)
		{
			MovePenTo(draw_coord_x,draw_coord_y);
			DrawBitmap(board_letters[letter_index]); 		
			++letter_index;
			draw_coord_x+=x_delta;
		}
	
	
		draw_coord_x=x_start;
		draw_coord_y+=y_delta;
		
	}
		 
}	

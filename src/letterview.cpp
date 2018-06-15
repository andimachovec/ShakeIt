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
	
	SetHighColor(242,188,44);
	FillRect(update_rect);
	
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
		board_letters[i] = BTranslationUtils::GetBitmap(B_PNG_FORMAT,letter_filenames[i].c_str());		
	}	 

}	



//-----------------------------------------------------------------------------
void LetterView::draw_bitmaps()
//-----------------------------------------------------------------------------
{

	SetDrawingMode(B_OP_ALPHA);
	
	
	int view_width=static_cast<int>(Frame().Width());
	int view_height=static_cast<int>(Frame().Height());
	int bitmap_width=static_cast<int>(board_letters[0]->Bounds().Width());
	int bitmap_height=static_cast<int>(board_letters[0]->Bounds().Height());


	int x_delta=80;
	int y_delta=80;	
	int x_start=(view_width - (x_delta * 3) - bitmap_width) / 2;
	int y_start=(view_height - (y_delta * 3) - bitmap_height) / 2;
		
	//std::cout << "x_delta: " << x_delta << std::endl;
	
	
	
	
	
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

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

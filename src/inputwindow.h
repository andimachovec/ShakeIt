#ifndef INPUTWINDOW_H
#define INPUTWINDOW_H

#include <Window.h>
#include <TextView.h>
#include <LayoutBuilder.h>
#include <Layout.h>
#include <LayoutItem.h>


class InputWindow : public BWindow
{
	
	public:
		InputWindow();
	
	
	private:
		BTextView *words_textview;
		
};	



#endif

#include "mainwindow.h"

//----------------------------------------------------------------------------
MainWindow::MainWindow(void)
	:BWindow(BRect(100,100,620,500),APPTITLE, B_TITLED_WINDOW, B_ASYNCHRONOUS_CONTROLS)
//----------------------------------------------------------------------------
{
	
	//initialize GUI Objects
	top_menu_bar = new BMenuBar("topmenubar");
	
	
	//build the menu layout
	BLayoutBuilder::Menu<>(top_menu_bar)
		.AddMenu(B_TRANSLATE("File"))
			.AddItem(B_TRANSLATE("Quit"), B_QUIT_REQUESTED, 'Q')
		.End()
		.AddMenu(B_TRANSLATE("Help"))
			.AddItem(B_TRANSLATE("About"), MW_ABOUT)
		.End()
	.End();	
		
	
	//build the main layout
	BLayoutBuilder::Group<>(this, B_VERTICAL,0)
		.SetInsets(0)
		.Add(top_menu_bar)
		.AddGroup(B_HORIZONTAL)
			
		.End()	
	.Layout();	
		
	

	


}


//----------------------------------------------------------------------------
void MainWindow::MessageReceived(BMessage *msg)
//----------------------------------------------------------------------------
{
	
	switch (msg->what)	
	{
		
		
		
		case MW_ABOUT:
		{
			be_app->PostMessage(B_ABOUT_REQUESTED);
			break;	
		}		
		
		
				
		default:
		{
			BWindow::MessageReceived(msg);
			break;
		}
	}

}	



//----------------------------------------------------------------------------
bool MainWindow::QuitRequested(void)
//----------------------------------------------------------------------------
{
	
	be_app->PostMessage(B_QUIT_REQUESTED);	
	return true;
}	





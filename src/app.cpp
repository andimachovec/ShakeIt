#include "app.h"

//----------------------------------------------------------------------------
App::App(void)
		: BApplication(APP_SIGNATURE)
//----------------------------------------------------------------------------
{
}	



//----------------------------------------------------------------------------
void App::MessageReceived(BMessage *msg)
//----------------------------------------------------------------------------
{
	
	switch(msg->what)
	{
		
		case TV_TIME_OVER:
		{
			main_window->PostMessage(msg);	
			break;
		}
			
		default:
		{
			BApplication::MessageReceived(msg);
			break;
		}
	
	}

}


//----------------------------------------------------------------------------
void App::AboutRequested(void)
//----------------------------------------------------------------------------
{
	
	BAboutWindow *aboutwindow = new BAboutWindow(APPTITLE, APP_SIGNATURE);
	
	const char *authors[] =
	{
		APPAUTHOR,
		NULL
	};
	
	
	aboutwindow->AddCopyright(APPCOPYRIGHTYEAR, APPCOPYRIGHTNAME);
	aboutwindow->AddAuthors(authors);
	aboutwindow->SetVersion(APPVERSION);
	aboutwindow->AddDescription(B_TRANSLATE(APPDESCRIPTION));
	aboutwindow->AddExtraInfo(B_TRANSLATE(APPEXTRAINFO));
	//aboutwindow->AddSpecialThanks("APPSPECIALTHANKS");
	aboutwindow->Show();
	
}



//----------------------------------------------------------------------------
bool App::QuitRequested(void)
//----------------------------------------------------------------------------
{
	
	return true; 
	
}


//----------------------------------------------------------------------------
void App::ReadyToRun(void)
//----------------------------------------------------------------------------
{

	main_window = new MainWindow();
	input_window = new InputWindow();
	//main_window->CenterOnScreen();
	main_window->Show();
	input_window->Show();
}	


//----------------------------------------------------------------------------
int main(int argc, char **argv)
//----------------------------------------------------------------------------
{
	
	App *haiku_app = new App();
	haiku_app->Run();
	
	delete haiku_app;
	
	return 0;
	
}	

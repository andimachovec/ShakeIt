#ifndef APP_H
#define APP_H

#include <Application.h>
#include <SupportDefs.h>
#include <AboutWindow.h>
#include <Catalog.h>

#include "mainwindow.h"
#include "defs.h"

#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "App"


class App : public BApplication
{

	public:
		App(void);
		void MessageReceived(BMessage *msg);
		void AboutRequested(void);
		bool QuitRequested(void);
		void ReadyToRun(void);

	private:
		MainWindow *mainwindow;
		
};


#endif

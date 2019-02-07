#ifndef STATUSVIEW_H
#define STATUSVIEW_H

#include <StringView.h>
#include <string>

class StatusView : public BStringView {
public:
	StatusView();
	void UpdateStatus();

private:

	std::string fDataDirectory;

};



#endif

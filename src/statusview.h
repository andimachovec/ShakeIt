#ifndef STATUSVIEW_H
#define STATUSVIEW_H

#include <StringView.h>


class StatusView : public BStringView {
public:
	StatusView();
	void UpdateStatus();

};

#endif

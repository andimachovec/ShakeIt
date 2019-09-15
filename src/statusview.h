/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */
 
#ifndef STATUSVIEW_H
#define STATUSVIEW_H

#include <StringView.h>
#include <string>

class StatusView : public BStringView {
public:
	StatusView(std::string DataDirectory);
	void UpdateStatus();

private:

	std::string fDataDirectory;

};



#endif

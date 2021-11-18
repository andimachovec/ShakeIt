/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#ifndef STATUSVIEW_H
#define STATUSVIEW_H

#include <StringView.h>
#include <String.h>
#include <Path.h>

class StatusView : public BStringView {
public:
	StatusView();
	void UpdateStatus();

private:

};

#endif

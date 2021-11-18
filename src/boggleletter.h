/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#ifndef BOGGLELETTER_H
#define BOGGLELETTER_H

#include <string>

class BoggleLetter {
public:
	BoggleLetter();
	std::string GetName();
	int	GetOrientation();
	void SetOrientation(int Orientation);
	void SetName(std::string Name);

private:
	std::string name;
	int orientation;
};


#endif

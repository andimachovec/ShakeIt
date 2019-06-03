/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */
 
#include "boggleletter.h"


#include <string>

//-----------------------------------------------------------------------------
BoggleLetter::BoggleLetter(std::string Name)
//-----------------------------------------------------------------------------
{

	name=Name;
	orientation=0;

}


//-----------------------------------------------------------------------------
std::string BoggleLetter::GetName()
//-----------------------------------------------------------------------------
{

	return name;

}


//-----------------------------------------------------------------------------
void BoggleLetter::SetOrientation(int Orientation)
//-----------------------------------------------------------------------------
{

	orientation=Orientation;

}


//-----------------------------------------------------------------------------
int BoggleLetter::GetOrientation()
//-----------------------------------------------------------------------------
{

	return orientation;

}



//-----------------------------------------------------------------------------
void BoggleLetter::SetName(std::string Name)
//-----------------------------------------------------------------------------
{
	name=Name;
}


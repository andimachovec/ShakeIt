/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#include "boggledie.h"

//-----------------------------------------------------------------------------
BoggleDie::BoggleDie()
//-----------------------------------------------------------------------------
{

		for (int i=0; i<6; ++i)
		{
			letters[i]=BoggleLetter();
		}

		active_letter_position=0;

}



//-----------------------------------------------------------------------------
BoggleLetter& BoggleDie::GetActiveLetter()
//-----------------------------------------------------------------------------
{

	return letters[active_letter_position];

}



//-----------------------------------------------------------------------------
void BoggleDie::SetActiveLetter(int Position)
//-----------------------------------------------------------------------------
{

	active_letter_position=Position;

}



//-----------------------------------------------------------------------------
void BoggleDie::SetActiveLetterOrientation(int Orientation)
//-----------------------------------------------------------------------------
{

	letters[active_letter_position].SetOrientation(Orientation);

}



//-----------------------------------------------------------------------------
void BoggleDie::SetLetters(std::array<std::string, 6> Letters)
//-----------------------------------------------------------------------------
{

	for (int i=0; i<6; ++i)
		{
			letters[i].SetName(Letters[i]);
		}

}







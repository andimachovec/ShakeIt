/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */
 
#ifndef BOGGLEDIE_H
#define BOGGLEDIE_H

#include <string>

#include "boggleletter.h"

class BoggleDie
{

	public:
		BoggleDie(std::string Letters[6]);
		BoggleLetter *GetActiveLetter();
		void SetActiveLetter(int Position);
		void SetActiveLetterOrientation(int Orientation);
		void SetLetters(std::string Letters[6]);


	private:
		BoggleLetter *letters[6];
		int active_letter_position;
		
};

#endif

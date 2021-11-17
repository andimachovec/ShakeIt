/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#ifndef BOGGLEDIE_H
#define BOGGLEDIE_H

#include <string>
#include <array>
#include "boggleletter.h"

class BoggleDie
{

	public:
		BoggleDie();
		BoggleLetter& GetActiveLetter();
		void SetActiveLetter(int Position);
		void SetActiveLetterOrientation(int Orientation);
		void SetLetters(std::array<std::string, 6> Letters);


	private:
		std::array<BoggleLetter, 6> letters;
		int active_letter_position;

};

#endif

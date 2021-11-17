/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#ifndef BOGGLEBOARD_H
#define BOGGLEBOARD_H

#include <string>
#include <array>
#include "boggledie.h"

class BoggleBoard
{
	public:
		BoggleBoard();
		BoggleDie& GetDie(int position);
		void Shake();
		void LoadDice();

	private:
		std::array<BoggleDie,16> dice;
};

#endif

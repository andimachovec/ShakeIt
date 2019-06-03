/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */
 
#ifndef BOGGLEBOARD_H
#define BOGGLEBOARD_H

#include <string>

#include "boggledie.h"

class BoggleBoard
{

	public:
		BoggleBoard(std::string DiceFilename);
		BoggleDie *GetDie(int position);		
		void Shake();
		void LoadDiceFile(std::string DiceFilename);

	private:
		BoggleDie *boggle_dice[16];
		void load_data_from_file();

		std::string dice_filename;
		std::string letters[16][6];

};

#endif

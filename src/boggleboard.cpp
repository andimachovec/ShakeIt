/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#include "boggleboard.h"
#include "datainterface.h"
#include "configparser.h"

#include <ctime>
#include <chrono>
#include <iostream>
#include <algorithm>


//-----------------------------------------------------------------------------
BoggleBoard::BoggleBoard()
//-----------------------------------------------------------------------------
{

	//initialize dice objects
	for(int i=0; i < 16; ++i)
	{
		dice[i] = BoggleDie();
	}


	LoadDice();

}




//-----------------------------------------------------------------------------
BoggleDie& BoggleBoard::GetDie(int position)
//-----------------------------------------------------------------------------
{


	return dice[position];

}



//-----------------------------------------------------------------------------
void BoggleBoard::Shake()
//-----------------------------------------------------------------------------
{

	//randomize the position of each die on the board
	std::random_shuffle(std::begin(dice),std::end(dice));

	//randomize the orientation of each die
	srand(time(NULL));

	for (int i=0; i<16; ++i)
	{
		int random_number = (rand() % 6);
		dice[i].SetActiveLetter(random_number);
		random_number = (rand() % 4);
		dice[i].SetActiveLetterOrientation(random_number);
	}

}



//-----------------------------------------------------------------------------
void BoggleBoard::LoadDice()
//-----------------------------------------------------------------------------
{

	std::array<std::array<std::string, 6>,16> letters;
	DataInterface::Data().GetDiceLetters(ConfigParser::Config().GetGameLanguage(), letters);

	for(int i=0; i<16; ++i)
	{
		dice[i].SetLetters(letters[i]);
	}

}





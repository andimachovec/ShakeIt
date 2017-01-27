#ifndef BOGGLEBOARD_H
#define BOGGLEBOARD_H


#include <ctime>
#include <chrono>
#include <iostream>
#include <algorithm>

#include "boggledie.h"

class BoggleBoard
{

	public:
		BoggleBoard(void);
		BoggleDie *GetDie(int position);		
		void Shake(void);

	private:
		BoggleDie *boggle_dice[16];


};

#endif

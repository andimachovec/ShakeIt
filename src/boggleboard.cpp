#include "boggleboard.h"


#include <ctime>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <fstream>


//-----------------------------------------------------------------------------
BoggleBoard::BoggleBoard(std::string DiceFilename)
//-----------------------------------------------------------------------------
{

	dice_filename=DiceFilename;
	load_data_from_file();
		
	
	for (int i=0; i<16; ++i)
	{		
		boggle_dice[i] = new BoggleDie(letters[i]);	
	}

}



//-----------------------------------------------------------------------------
BoggleDie *BoggleBoard::GetDie(int position)
//-----------------------------------------------------------------------------
{
	
	
	return boggle_dice[position];

}



//-----------------------------------------------------------------------------
void BoggleBoard::Shake()
//-----------------------------------------------------------------------------
{

	//randomize the position of each die on the board
	std::random_shuffle(std::begin(boggle_dice),std::end(boggle_dice));


	//randomize the orientation of each die
	srand(time(NULL));	
	
	for (int i=0; i<16; ++i)
	{

		int random_number = (rand() % 6);		
		boggle_dice[i]->SetActiveLetter(random_number);
		random_number = (rand() % 4);
		boggle_dice[i]->SetActiveLetterOrientation(random_number);
	}

	
}



//-----------------------------------------------------------------------------
void BoggleBoard::LoadDiceFile(std::string DiceFilename)
//-----------------------------------------------------------------------------
{
	
	dice_filename=DiceFilename;
	load_data_from_file();
		
	
	for (int i=0; i<16; ++i)
	{		
		boggle_dice[i]->SetLetters(letters[i]);	
	}

}



//-----------------------------------------------------------------------------
void BoggleBoard::load_data_from_file()
//-----------------------------------------------------------------------------
{	

	std::ifstream dice_file;
	dice_file.open(dice_filename);

	std::string line;
	
	while (getline(dice_file,line))
	{

		if (line != "")
		{			
			//split line in the different parameters
			int die_number;
			int side_number;
			std::string letter;

			size_t position1=line.find(",");
			die_number=std::stoi(line.substr(0,position1));
						
			++position1;
			size_t position2=line.find(",",position1);
			side_number=std::stoi(line.substr(position1,position2-position1));			

			letter=line.substr(position2+1); 

			//add letter to the letter array
			letters[die_number][side_number]=letter;
		}

	}

	dice_file.close();

}


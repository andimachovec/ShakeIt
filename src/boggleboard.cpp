#include "boggleboard.h"

//-----------------------------------------------------------------------------
BoggleBoard::BoggleBoard(void)
//-----------------------------------------------------------------------------
{

	//data for the boggle dice
	std::string letters[16][6];
	

		letters[0][0]="G";
		letters[0][1]="I";
		letters[0][2]="V";
		letters[0][3]="T";
		letters[0][4]="E";
		letters[0][5]="N";
	
		letters[1][0]="O";
		letters[1][1]="T";
		letters[1][2]="E";
		letters[1][3]="N";
		letters[1][4]="D";
		letters[1][5]="S";
	
		letters[2][0]="T";
		letters[2][1]="P";
		letters[2][2]="E";
		letters[2][3]="U";
		letters[2][4]="S";
		letters[2][5]="L";
	
		letters[3][0]="I";
		letters[3][1]="A";
		letters[3][2]="O";
		letters[3][3]="M";
		letters[3][4]="S";
		letters[3][5]="R";
	
		letters[4][0]="F";
		letters[4][1]="X";
		letters[4][2]="I";
		letters[4][3]="A";
		letters[4][4]="O";
		letters[4][5]="R";
	
		letters[5][0]="M";
		letters[5][1]="C";
		letters[5][2]="A";
		letters[5][3]="E";
		letters[5][4]="P";
		letters[5][5]="D";
	
		letters[6][0]="H";
		letters[6][1]="I";
		letters[6][2]="R";
		letters[6][3]="S";
		letters[6][4]="E";
		letters[6][5]="N";
	
		letters[7][0]="B";
		letters[7][1]="R";
		letters[7][2]="T";
		letters[7][3]="I";
		letters[7][4]="L";
		letters[7][5]="A";
	
		letters[8][0]="R";
		letters[8][1]="L";
		letters[8][2]="W";
		letters[8][3]="I";
	    letters[8][4]="U";
		letters[8][5]="E";
	
		letters[9][0]="U";
		letters[9][1]="N";
		letters[9][2]="E";
		letters[9][3]="L";
		letters[9][4]="G";
		letters[9][5]="Y";
	
		letters[10][0]="H";
		letters[10][1]="E";
		letters[10][2]="I";
		letters[10][3]="S";
		letters[10][4]="E";
		letters[10][5]="F";
		
		letters[11][0]="S";
		letters[11][1]="R";
		letters[11][2]="E";
		letters[11][3]="A";
		letters[11][4]="C";
		letters[11][5]="L";
	
		letters[12][0]="O";
		letters[12][1]="B";
		letters[12][2]="J";
		letters[12][3]="A";
		letters[12][4]="M";
		letters[12][5]="Q";
	
		letters[13][0]="O";
		letters[13][1]="A";
		letters[13][2]="I";
		letters[13][3]="A";
		letters[13][4]="E";
		letters[13][5]="T";
	
		letters[14][0]="D";
		letters[14][1]="N";
		letters[14][2]="V";
		letters[14][3]="A";
		letters[14][4]="E";
		letters[14][5]="Z";
	
		letters[15][0]="N";
		letters[15][1]="O";
		letters[15][2]="U";
		letters[15][3]="K";
		letters[15][4]="E";
		letters[15][5]="T";
		
	

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
void BoggleBoard::Shake(void)
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

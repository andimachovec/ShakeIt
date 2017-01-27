#include "boggledie.h"

//-----------------------------------------------------------------------------
BoggleDie::BoggleDie(std::string Letters[6])
//-----------------------------------------------------------------------------
{

		for (int i=0; i<6; ++i)
		{
			letters[i]=new BoggleLetter(Letters[i]);
		}


		active_letter_position=0;
		
}



//-----------------------------------------------------------------------------
BoggleLetter *BoggleDie::GetActiveLetter(void)
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

	letters[active_letter_position]->SetOrientation(Orientation);
	
}



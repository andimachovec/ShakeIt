/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#include "gamecontroller.h"
#include "configparser.h"

#include <iostream>
#include <sstream>
#include <exception>
#include <system_error>
#include <algorithm>


GameController::GameController(	const std::vector<std::string> &Dictionary,
								const std::array<std::array<std::string, 6>, 16> &DiceLetters,
								int MinWordLength)
	:
	boggle_board(DiceLetters),
	dictionary_words(Dictionary),
	minimum_word_length(MinWordLength)
{

	//initialize properties
	points_total=0;
	round_running=false;
	game_running=false;

	//initialize the already used matrix to false for all positions
	//(the matrix is supplied by value to word_search and not actually changed, so it´s sufficient to initialize it once here)
	initialize_already_used_matrix();

}


GameController::~GameController()
{

}


void
GameController::StartGame()
{

	game_running=true;

}


void
GameController::GameFinished()
{

	game_running=false;

}


void
GameController::StartRound()
{

	boggle_board.Shake();
	setup_letter_matrix();

	round_running=true;

}


round_results
GameController::RoundFinished()
{

	round_running=false;

	round_results results;
	std::vector<std::string>::iterator word_list_iter;
	int points_per_word=0;
	int validation_result;

	//clear the duplicate checklist
	duplicate_checklist.clear();

	//set points for the current round to 0
	points_current_round=0;

	//loop through word list, check if the words are valid and give points if they are
	for (word_list_iter=word_list.begin();word_list_iter!=word_list.end();++word_list_iter)
	{
		validation_result=validate_word(*word_list_iter);

		if ( validation_result == 0)  //if word is valid -> continue;
		{
			points_per_word=give_points(*word_list_iter);
			points_current_round+=points_per_word;
		}
		else
		{
			points_per_word=0;
		}

		//add the validation result and the points to the results vector
		results.push_back(std::make_pair(validation_result,points_per_word));
	}

	points_total+=points_current_round;


	//compute the list of missing words that the player didn´t find
	find_missing_words();


	return results;

}


std::vector<std::string>
GameController::GetBoardLetters()
{

	std::vector<std::string> board_letters;

	for (int i=0;i<4;++i)
	{
		for (int j=0;j<4;++j)
		{

			std::string letter_string="";
			letter_string+=letter_matrix[i][j];
			board_letters.push_back(letter_string);

		}
	}

	return board_letters;

}


std::vector<int>
GameController::GetBoardLetterOrientation()
{

	std::vector<int> board_letter_orientation;

	for (int i=0;i<4;++i)
	{
		for (int j=0;j<4;++j)
		{
			board_letter_orientation.push_back(letter_orientation_matrix[i][j]);
		}
	}

	return board_letter_orientation;

}


void
GameController::SetWordList(std::vector<std::string> WordList)
{

	word_list=WordList;

}


int
GameController::GetCurrentRoundPoints()
{

	return points_current_round;

}


int
GameController::GetTotalPoints()
{

	return points_total;

}


std::vector<std::string>
GameController::GetMissingWords()
{

	return missing_words;

}


bool
GameController::IsRoundRunning()
{

	return round_running;

}


bool
GameController::IsGameRunning()
{

	return game_running;

}


void
GameController::SetDictionary(std::vector<std::string> Dictionary)
{

	if (!round_running)
	{
		dictionary_words = Dictionary;
	}

}


void
GameController::SetMinWordLength(int MinWordLength)
{
	if (!round_running)
	{
		minimum_word_length = MinWordLength;
	}
}


void
GameController::SetDiceLetters(std::array<std::array<std::string, 6>, 16> DiceLetters)
{
	if (!round_running)
	{
		boggle_board.SetDiceLetters(DiceLetters);
	}

}




int
GameController::validate_word(std::string word)
{

	/*
	Return codes:
	0 -> valid
	1 -> too short
	2 -> not possible
	3 -> not in dictionary
	4 -> duplicate
	*/

	int returncode;
	size_t word_length=word.length();

	//check if the word is a duplicate
	if (!check_duplicate(word))  //check duplicate returns true if the word is a duplicate
	{
		//check if the word is minimum character length
		if (word_length >= minimum_word_length)
		{
			//check if the word is possible with the current letters on the board
			if (check_possible(word))
			{
				//check if word is in the dictionary
				if (check_dictionary(word))
				{
					returncode=0;  //word is valid
				}
				else
				{
					returncode=3; //word is not in dictionary
				}
			}
			else
			{
			returncode=2; //word is not possible
			}
		}
		else
		{
			returncode=1; //word is too short
		}
	}
	else
	{
		returncode=4;
	}

	return returncode;

}


bool
GameController::check_duplicate(std::string word)
{

	bool is_duplicate=false;

	//if the check list is empty, just add the word
	if (duplicate_checklist.empty())
	{
		duplicate_checklist.push_back(word);
	}
	else
	{
		std::vector<std::string>::iterator checklist_iter;

		for (checklist_iter=duplicate_checklist.begin();checklist_iter!=duplicate_checklist.end();++checklist_iter)
		{
			if (*checklist_iter == word)
			{
				is_duplicate=true;
			}
		}

		if (!is_duplicate)
		{
			duplicate_checklist.push_back(word);
		}
	}

	return is_duplicate;

}


bool
GameController::check_possible(std::string word)
{

	bool is_possible=false;

	//find starting points
	std::vector<coordinates> starting_points = find_starting_points(word);
	std::vector<coordinates>::iterator starting_points_iter;

	//loop through starting points and start the word search at each starting point
	for (starting_points_iter=starting_points.begin();starting_points_iter!=starting_points.end(); ++starting_points_iter)
	{
		// start the recursive word_search algorithm
		word_completed=false; //reset word_completed status flag
		if (word_search(word,starting_points_iter->first,starting_points_iter->second,1,already_used_matrix))
		{
			is_possible=true;
			goto word_complete; //see comment at the goto statement in word_search();
		}
	}

	word_complete: ; //label to jump to for goto

	return is_possible;

}


bool
GameController::check_dictionary(std::string word)
{

	return (std::find(dictionary_words.begin(), dictionary_words.end(), word) != dictionary_words.end());

}


void
GameController::find_missing_words()
{

	//empty the missing words vector
	missing_words.clear();

	//loop through the words in the dictionary and check if a word is applicable
	std::vector<std::string>::iterator dictionary_iter;
	for(dictionary_iter = dictionary_words.begin(); dictionary_iter != dictionary_words.end();
		++dictionary_iter)
	{
		std::string dictionary_word = *dictionary_iter;

		if (dictionary_word.length() >= minimum_word_length) //check if the word has the minimum length
		{
			if (check_possible(dictionary_word)) //check if the word is possible
			{
				//check that the word is not in the list of words that the player found
				if (std::find(word_list.begin(), word_list.end(), dictionary_word) == word_list.end())
				{
					missing_words.push_back(dictionary_word);
				}
			}
		}
	}

}


int
GameController::give_points(std::string word)
{

	int word_length = word.length();
	int points=0;

	if (word_length <= 4) 	//words below minimum length (3 characters at the moment)
	{						//are reported as invalid by validate_word()
		points=1;
	}

	else if (word_length == 5)
	{
		points=2;
	}

	else if (word_length == 6)
	{
		points=3;
	}

	else if (word_length == 7)
	{
		points=5;
	}

	else if (word_length >= 8)
	{
		points=11;
	}

	return points;

}


void
GameController::setup_letter_matrix()
{

	int row=0;
	int col=0;

	for (int i=0; i<16; ++i)
	{
		BoggleDie current_die = boggle_board.GetDie(i);
		BoggleLetter current_letter = current_die.GetActiveLetter();
		std::string output_str(current_letter.GetName());
		int letter_orientation=current_letter.GetOrientation();

		//fill letters and their orientation into matrix (used later for validation)
		letter_matrix[row][col]=output_str[0];
		letter_orientation_matrix[row][col]=letter_orientation;

		if (col == 3)
		{
			col=0;
			++row;
		}
		else
		{
			++col;
		}
	}

}


void
GameController::initialize_already_used_matrix()
{

	for (int row=0;row<4;++row)
	{
		for (int col=0;col<4;++col)
		{
			already_used_matrix[row][col]=false;
		}
	}

}


std::vector<coordinates>
GameController::find_starting_points(std::string word)
{

	std::vector<coordinates> found_locations;
	char letter=word.c_str()[0];

	for (int row=0;row<4;++row)
	{
		for(int col=0;col<4;++col)
		{
			if (letter == letter_matrix[row][col])
			{
				//add the position to the vector
				found_locations.push_back(std::make_pair(row,col));
			}
		}
	}

	return found_locations;

}


bool
GameController::word_search(std::string word,int start_row, int start_col,unsigned int position_in_word,bool_matrix already_used)
{

	bool valid=false;
	char letter=word.c_str()[position_in_word];

	//mark starting point as already used
	already_used[start_row][start_col]=true;

	//go through all adjacent rows
	for(int check_row=start_row-1;check_row<=start_row+1;++check_row)
	{
		//go trough all adjacent columns
		for(int check_col=start_col-1;check_col<=start_col+1;++check_col)
		{
			//only use valid positions (within board boundaries)
			if ((check_row>=0) and (check_row <=3) and (check_col>=0) and (check_col<=3))
			{
				//skip the position of the starting point and check if the position is not marked as already used
				if ((!((check_row==start_row) and (check_col==start_col))) and (!(already_used[check_row][check_col])))
				{
					//check if the letter matches and add the position to the return vector if it does
					if (letter == letter_matrix[check_row][check_col])
					{
						//if we have the a match for the last letter we have finished successfully
						if ((position_in_word+1) == word.length())
						{
							valid=true;
							word_completed=true;
							goto word_complete; //shock, horror, I´ve used goto ... indeed I seem to have finally stumbled upon one
												// of the few cases where using goto is not considered bad practice
						}
						else //match within the word, continue
						{
							if (!word_completed)
							{
								valid=word_search(word,check_row,check_col,position_in_word+1,already_used);
							}
						}
					}
				}
			}
		}
	}

	word_complete: ; //label to jump to with goto when the word is complete

	return valid;

}


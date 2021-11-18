/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H


#include <string>
#include <vector>
#include <array>

#include "boggleboard.h"
#include "boggledie.h"


typedef std::pair<int,int> coordinates;
typedef std::array<std::array<bool,4>,4> bool_matrix;
typedef std::array<std::array<char,4>,4> char_matrix;
typedef std::array<std::array<int,4>,4> int_matrix;
typedef std::vector<std::pair<int,int> > round_results;
typedef std::vector<std::pair<int,int> >::iterator round_results_iterator;


class GameController
{

	public:
		GameController(	const std::vector<std::string> &Dictionary,
						const std::array<std::array<std::string, 6>, 16> &DiceLetters,
						int MinWordLength);
		~GameController();

		void StartGame();
		void GameFinished();
		void StartRound();
		round_results RoundFinished();
		bool IsRoundRunning();
		bool IsGameRunning();

		std::vector<std::string> GetBoardLetters();
		std::vector<int> GetBoardLetterOrientation();
		int GetCurrentRoundPoints();
		int GetTotalPoints();
		std::vector<std::string> GetMissingWords();

		void SetWordList(std::vector<std::string> WordList);
		void SetDictionary(std::vector<std::string> Dictionary);
		void SetMinWordLength(int MinWordLength);
		void SetDiceLetters(std::array<std::array<std::string, 6>, 16> DiceLetters);

	private:
		//methods
		int validate_word(std::string word);					//validate a word according to game rules

		bool check_possible(std::string word);					//used by validate_word() to check if the word is possible with the current letters on the board
		bool check_dictionary(std::string word);				//used by validate_word() to check if the word is valid according to the dictionary
		bool check_duplicate(std::string word);					//used by validate_word() to check for duplicates

		void setup_letter_matrix();							//get the current letters from the GameDie objects and put them into a 4x4 matrix (used for validation)
		void initialize_already_used_matrix(); 				//initialize the already used matrix for check_possible()
		std::vector<coordinates> find_starting_points(std::string word);	//used by check_possible to find the starting points for word_search()
		bool word_search(std::string word,int start_row, int start_col,unsigned int position_in_word,bool_matrix already_used); //recursive method used by check_possible to follow the paths and check if the word is really possible

		int	give_points(std::string word);						//give points for a word according to game rules
		void find_missing_words();      //finds the words in the dictionary that are possible but that the player didn´t find

		//properties
		BoggleBoard boggle_board;

		char_matrix	letter_matrix;				//matrix of letters on the game board, populated by setup_letter_matrix()
		bool_matrix	already_used_matrix; 		//bool matrix of the positions that were already used by word_search()
		int_matrix letter_orientation_matrix;			//integer matrix of the orientation of the letters on the board


		bool word_completed;					//flag that is used by word_search to know when to stop ;-)
		std::vector<std::string> word_list;		//list of the entered words
		std::vector<std::string> duplicate_checklist;	//already processed words in wordlist are added here by RoundFinished(). used by check_duplicate();

		int points_total;
		int points_current_round;
		std::vector<std::string> dictionary_words;
		unsigned int minimum_word_length;
		std::vector<std::string> missing_words;

		bool game_running;
		bool round_running;

};


#endif

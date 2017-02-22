#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H


#include <string>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <sstream>
#include <exception>

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
		GameController(std::string DictionaryFile, int MinimumWordLength);			//constructor
		void StartGame();									//starts the game
		void GameFinished();								//finishes the game
		void StartRound();									//starts a game round
		round_results RoundFinished();						//finishes a game round	
		std::vector<std::string> GetBoardLetters();			//called by MainFrame to get the letter list for display on the board
		std::vector<int> GetBoardLetterOrientation();       //called by Mainframe to get the orientation of the letters on the board
		void SetWordList(std::vector<std::string> WordList);	//called by MainFrame to give the word list from WordFrame back to GameController
		int GetCurrentRoundPoints();						//returns the points of the current (finished) round
		int GetTotalPoints();								//returns the total points in the game
		std::vector<std::string> GetMissingWords();         //returns the list of possible words that the player didn´t find 
															//for the last finished round 
															
		bool SetDictionaryFile(std::string DictionaryFile);
		bool SetMinimumWordLength(int MinimumWordLength);
																                   
		bool IsRoundRunning();
		bool IsGameRunning();
		
		
	private:
		
		//methods
		int validate_word(std::string word);					//validate a word according to game rules
		
		bool check_possible(std::string word);					//used by validate_word() to check if the word is possible with the current letters on the board
		bool check_dictionary(std::string word);				//used by validate_word() to check if the word is valid according to the dictionary
		bool check_duplicate(std::string word);					//used by validate_word() to check for duplicates
		
		void setup_letter_matrix(void);							//get the current letters from the GameDie objects and put them into a 4x4 matrix (used for validation)	
		void initialize_already_used_matrix(void); 				//initialize the already used matrix for check_possible()
		std::vector<coordinates> find_starting_points(std::string word);	//used by check_possible to find the starting points for word_search()
		bool word_search(std::string word,int start_row, int start_col,int position_in_word,bool_matrix already_used); //recursive method used by check_possible to follow the paths and check if the word is really possible

		int	give_points(std::string word);						//give points for a word according to game rules
		void find_missing_words(void);      //finds the words in the dictionary that are possible but that the player didn´t find
		
		
		
		//properties
		BoggleBoard *boggle_board;				//BoggleBoard object used for the game
		
		char_matrix	letter_matrix;				//matrix of letters on the game board, populated by setup_letter_matrix()
		bool_matrix	already_used_matrix; 		//bool matrix of the positions that were already used by word_search()
		int_matrix letter_orientation_matrix;			//integer matrix of the orientation of the letters on the board
		
		
		bool word_completed;					//flag that is used by word_search to know when to stop ;-)		
		std::vector<std::string> word_list;		//list of the entered words
		std::vector<std::string> duplicate_checklist;	//already processed words in wordlist are added here by RoundFinished(). used by check_duplicate();
		
		int points_total;						//total points in the game
		int points_current_round;				//points for the current round
		int minimum_word_length;				//minimum word length for the valid words 	
		std::string dictionary_filename;		//filename of the wordlist file used for the dictionary check and to find missing words
		std::vector<std::string> missing_words; //list of the possible words that the user didnt find (updated in RoundFinished())

		bool game_running;
		bool round_running;

};


#endif

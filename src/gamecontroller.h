#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H


#include <string>
#include <vector>
#include <array>
#include <sqlite3.h>

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
		GameController(std::string DictionaryFile, std::string DiceFile, int MinimumWordLength);			
		~GameController();		
		void StartGame();									
		void GameFinished();								
		void StartRound();									
		round_results RoundFinished();						
		std::vector<std::string> GetBoardLetters();			
		std::vector<int> GetBoardLetterOrientation();       
		void SetWordList(std::vector<std::string> WordList);	
		int GetCurrentRoundPoints();						
		int GetTotalPoints();								
		std::vector<std::string> GetMissingWords();         
															
															
		bool SetDictionaryFile(std::string DictionaryFileName);
		bool SetDiceFile(std::string DiceFileName);		
		bool SetMinimumWordLength(int MinimumWordLength);
																                   
		bool IsRoundRunning();
		bool IsGameRunning();
		
		
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
		void open_dictionary_db();
		void close_dictionary_db();
		
		//properties
		BoggleBoard *boggle_board;				
		
		char_matrix	letter_matrix;				//matrix of letters on the game board, populated by setup_letter_matrix()
		bool_matrix	already_used_matrix; 		//bool matrix of the positions that were already used by word_search()
		int_matrix letter_orientation_matrix;			//integer matrix of the orientation of the letters on the board
		
		
		bool word_completed;					//flag that is used by word_search to know when to stop ;-)		
		std::vector<std::string> word_list;		//list of the entered words
		std::vector<std::string> duplicate_checklist;	//already processed words in wordlist are added here by RoundFinished(). used by check_duplicate();
		
		int points_total;						
		int points_current_round;				
		std::string dictionary_filename;		
		unsigned int minimum_word_length;						
		std::vector<std::string> missing_words; 

		bool game_running;
		bool round_running;

		sqlite3 *dictionary_db;
};


#endif

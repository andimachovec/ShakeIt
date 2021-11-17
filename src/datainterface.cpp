/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#include "datainterface.h"

#include <FindDirectory.h>
#include <Directory.h>

#include <exception>
#include <system_error>
#include <sqlite3.h>
#include <fstream>
#include <iostream>

DataInterface::DataInterface()
{

	find_directory(B_SYSTEM_NONPACKAGED_DATA_DIRECTORY, &fDataDirPath);
	BDirectory data_directory(fDataDirPath.Path());

	if (!data_directory.Contains("ShakeIt", B_DIRECTORY_NODE))
	{
		find_directory(B_SYSTEM_DATA_DIRECTORY, &fDataDirPath);
	}

	fDataDirPath.Append("ShakeIt");

}


DataInterface::~DataInterface()
{


}


void
DataInterface::GetDictionary(BString language, std::vector<std::string> &dictionary)
{
	dictionary.clear();

	BString dictionary_filename;
	dictionary_filename << fDataDirPath.Path() << "/languages/" << language << "/" << language << ".dict";

	//open database
	sqlite3 *dictionary_db = nullptr;
	int result = sqlite3_open_v2(dictionary_filename.String(), &dictionary_db, SQLITE_OPEN_READONLY, NULL);

	if (result != SQLITE_OK)
	{
		std::cout << "Error opening dictionary database" << std::endl;
		//TODO: throw error
	}

	//fetch data and fill into dictionary vector
	sqlite3_stmt *statement = nullptr;
	sqlite3_prepare_v2(dictionary_db,"select name from words order by name", -1, &statement, NULL);

	while (sqlite3_step(statement) != SQLITE_DONE)
	{
			std::string dictionary_word(reinterpret_cast<const char*>(sqlite3_column_text(statement,0)));
			dictionary.push_back(dictionary_word);
	}

	sqlite3_finalize(statement);

	//close database
	sqlite3_close(dictionary_db);

}


BPath&
DataInterface::GetDataDirectoryPath()
{
	return fDataDirPath;
}


BString
DataInterface::GetSoundFilename()
{
	BString sound_filename;
	sound_filename << fDataDirPath.Path() << "/shakeit.wav";
	return sound_filename;
}


BString
DataInterface::GetLanguageDescription(BString language)
{

	BString language_desc_filename;
	language_desc_filename << fDataDirPath.Path() << "/languages/" << language << "/" << language << ".desc";

	std::ifstream language_desc_file;
	language_desc_file.open(language_desc_filename.String());
	std::string language_desc;
	getline(language_desc_file,language_desc);
	language_desc_file.close();

	return BString(language_desc.c_str());
}


void
DataInterface::GetAvailableLanguages(std::vector<std::pair<BString, BString>> &available_languages)
{

	BPath languages_directory_path(fDataDirPath);
	languages_directory_path.Append("languages");
	BDirectory languages_directory(languages_directory_path.Path());
	BEntry language_dir_entry;

	while (languages_directory.GetNextEntry(&language_dir_entry) != B_ENTRY_NOT_FOUND)
	{
		if (language_dir_entry.IsDirectory())
		{
			BPath language_dir_path(&language_dir_entry);
			BString language_code(language_dir_path.Leaf());
			BString language_file_name(language_dir_path.Path());
			language_file_name+="/";
			language_file_name+=language_code;
			language_file_name+=".desc";

			std::ifstream language_desc_file;
			language_desc_file.open(language_file_name.String());
			if (language_desc_file.good())
			{
				std::string language_description;
				getline(language_desc_file,language_description);
				available_languages.push_back(std::make_pair(language_code,BString(language_description.c_str())));

				language_desc_file.close();
			}
		}
	}

}


void
DataInterface::GetDiceLetters(BString language, std::array<std::array<std::string, 6>,16> &letters)
{

	BString dice_filename;
	dice_filename << fDataDirPath.Path() << "/languages/" << language << "/" << language << ".dice";

	std::ifstream dice_file;
	dice_file.open(dice_filename.String());

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


DataInterface
&DataInterface::Data()
{

		static DataInterface *data = new DataInterface();
		return *data;

}



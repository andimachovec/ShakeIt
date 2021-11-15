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

DataInterface
&DataInterface::Data()
{

		static DataInterface *data = new DataInterface();
		return *data;

}



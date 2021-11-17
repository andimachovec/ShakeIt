/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */

#ifndef DATAINTERFACE_H
#define DATAINTERFACE_H

#include <String.h>
#include <Path.h>

#include <vector>
#include <string>
#include <utility>

#include "boggledie.h"


class DataInterface {
public:
	void GetDictionary(BString language, std::vector<std::string> &dictionary);
	BPath& GetDataDirectoryPath();
	BString GetSoundFilename();
	BString GetLanguageDescription(BString language);
	void GetAvailableLanguages(std::vector<std::pair<BString, BString>> &available_languages);
	void GetDiceLetters(BString language, std::array<std::array<std::string, 6>,16> &letters);
	static DataInterface &Data();

private:
	DataInterface();
	~DataInterface();
	BPath fDataDirPath;
};

#endif

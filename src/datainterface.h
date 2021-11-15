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

class DataInterface {
public:
	void GetDictionary(BString language, std::vector<std::string> &dictionary);
	BPath& GetDataDirectoryPath();
	BString GetSoundFilename();
	static DataInterface &Data();

private:
	DataInterface();
	~DataInterface();
	BPath fDataDirPath;
};

#endif

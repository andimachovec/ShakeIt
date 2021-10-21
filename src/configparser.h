/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */
 
#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <String.h>
#include <Message.h>
#include <Directory.h>

class ConfigParser {
public:

	void SetConfigDirectory(BDirectory directory);
	void CreateConfigFile();
	void ReadConfigFromFile();
	void WriteConfigToFile();
	BString GetGameLanguage();
	uint8 GetMinWordLength();
	bool GetSound();
	void SetGameLanguage(BString game_language);
	void SetMinWordLength(uint8 min_word_length);
	void SetSound(bool sound); 
	
	static ConfigParser &Config();		


private:
	ConfigParser();
	~ConfigParser();		
	BMessage fConfigMessage;
	BDirectory fConfigDirectory;	
};

#endif

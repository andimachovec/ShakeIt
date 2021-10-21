/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */
 
#include "configparser.h"

#include <File.h>
#include <exception>
#include <system_error>


const char *kConfigFilename = "/boot/home/config/settings/ShakeIt_settings";


ConfigParser::ConfigParser()
{
	
	
}


ConfigParser::~ConfigParser()
{


}


void
ConfigParser::ReadConfigFromFile() 
{	
	
	BFile *config_file = new BFile(kConfigFilename, B_READ_WRITE);
	status_t read_status = fConfigMessage.Unflatten(config_file);
	
	if (read_status != B_OK)
	{
		throw std::system_error(std::error_code(1, std::system_category()), "could not open config file");
	}	
	
	delete config_file;

}


void 
ConfigParser::WriteConfigToFile() 
{
	
	BFile *config_file = new BFile(kConfigFilename, B_READ_WRITE);	
	status_t write_status = fConfigMessage.Flatten(config_file);
	
	if (write_status != B_OK)
	{
		throw std::system_error(std::error_code(2, std::system_category()), "could not write to config file");
	}

}


BString 
ConfigParser::GetGameLanguage()
{
	const char *game_language;
	
	fConfigMessage.FindString("game_language", 0, &game_language);
	return BString(game_language);
	
}


uint8 
ConfigParser::GetMinWordLength()
{
	uint8 min_word_length;
	fConfigMessage.FindUInt8("minimum_word_length", 0, &min_word_length);

	return min_word_length;
}


bool 
ConfigParser::GetSound()
{
	bool sound;
	fConfigMessage.FindBool("sound", 0, &sound);
	
	return sound;

}


void
ConfigParser::SetGameLanguage(BString game_language)
{
	fConfigMessage.ReplaceString("game_language", 0, game_language.String());
}


void
ConfigParser::SetMinWordLength(uint8 min_word_length)
{
	fConfigMessage.ReplaceUInt8("minimum_word_length", 0, min_word_length);
}


void
ConfigParser::SetSound(bool sound)
{
	fConfigMessage.ReplaceBool("sound", 0, sound);
} 


ConfigParser 
&ConfigParser::Config()  
{

		static ConfigParser *config = new ConfigParser();
		return *config;

}



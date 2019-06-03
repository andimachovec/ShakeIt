/*
 * Copyright 2017-2019 Andi Machovec <andi.machovec@gmail.com>
 * All rights reserved. Distributed under the terms of the MIT license.
 *
 */
 
#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H


#include <map>
#include <string>
#include <tinyxml.h>


class ConfigParser
{

	public:
	
		
		std::string GetParameter(std::string parametername);	
		void SetParameter(std::string parametername, std::string value);
		void ReadConfigFromFile(std::string FileName);
		void WriteConfigToFile(std::string FileName);
		void SetConfigFileName(std::string ConfigFileName);
		
		static ConfigParser &Config();		


	private:

		ConfigParser();
		~ConfigParser();		
		TiXmlDocument xml_file;
		std::map<std::string,std::string> parameters;
		

};

#endif

#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H


#include <map>
#include <string>

#ifdef __HAIKU__
	#include "tinyxml.h"
#else
	#include <tinyxml.h>
#endif


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

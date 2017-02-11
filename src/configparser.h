#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <tinyxml.h>
#include <map>
#include <string>


class ConfigParser
{

	public:
	
		ConfigParser(const char *xmlfilename);
		std::string GetParam(std::string parametername);	
		bool SetParam(std::string parametername, std::string value);
		bool ReadConfig();
		bool WriteConfig();
		
		
	private:

		TiXmlDocument XMLFile;
		std::map<std::string,std::string> Parameters;
		

};

#endif


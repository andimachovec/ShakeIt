#include "configparser.h"

#include <exception>
#include <system_error>

//-----------------------------------------------------------------------------
ConfigParser::ConfigParser()
//-----------------------------------------------------------------------------
{
	
	TiXmlBase::SetCondenseWhiteSpace(false);
}

//-----------------------------------------------------------------------------
ConfigParser::~ConfigParser()
//-----------------------------------------------------------------------------
{


}


//-----------------------------------------------------------------------------
void ConfigParser::ReadConfigFromFile(std::string FileName) 
//-----------------------------------------------------------------------------
{
	
	//Load Content from XML file
	bool load_ok = xml_file.LoadFile(FileName);
	
	if (!load_ok)
	{
		throw std::system_error(std::error_code(1, std::system_category()), "could not open config file");
	}	
	
	
	// make sure the parameter map is empty
	parameters.clear();
	
	
	//loop through the XML elements and put parameters + their values into map
	
	TiXmlElement *RootNode = xml_file.RootElement();
	
	for(TiXmlElement *XMLElement = RootNode->FirstChildElement(); XMLElement != NULL; XMLElement = XMLElement->NextSiblingElement())
	{
		parameters[XMLElement->Value()] = XMLElement->GetText();			
	}
	
	
}


//-----------------------------------------------------------------------------
void ConfigParser::WriteConfigToFile(std::string FileName) 
//-----------------------------------------------------------------------------
{
	
	bool result_ok=xml_file.SaveFile(FileName);


	if (!result_ok)
	{
		throw std::system_error(std::error_code(2, std::system_category()), "could not write to config file");
	}

}


//-----------------------------------------------------------------------------
std::string ConfigParser::GetParameter(std::string parametername) 
//-----------------------------------------------------------------------------
{
	
	return parameters[parametername];
}


//-----------------------------------------------------------------------------
void ConfigParser::SetParameter(std::string parametername, std::string value) 
//-----------------------------------------------------------------------------
{


	if (parameters.find(parametername) == parameters.end()) //parameter doesn't exist
	{
		
		//add exception here
	}
	
	else {
		
		
		//change the value also in the XMLDocument Object in Memory
		
		TiXmlElement *RootNode = xml_file.RootElement();
		TiXmlElement *ParamElement = RootNode->FirstChildElement(parametername);
		ParamElement->FirstChild()->SetValue(value);
		
				
		//change the value in the parameter map	
		parameters[parametername] = value;
	
	}	
}


//-----------------------------------------------------------------------------
ConfigParser &ConfigParser::Config()  
//-----------------------------------------------------------------------------
{

		static ConfigParser *config = new ConfigParser();
		return *config;

}



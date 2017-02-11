#include "configparser.h"

//-----------------------------------------------------------------------------
ConfigParser::ConfigParser(const char *xmlfilename) : XMLFile(xmlfilename)
//-----------------------------------------------------------------------------
{
	
	TiXmlBase::SetCondenseWhiteSpace(false);
	ReadConfig();
	
	
}


//-----------------------------------------------------------------------------
bool ConfigParser::ReadConfig(void) //read parameters from XML config file
//-----------------------------------------------------------------------------
{
	
	//Load Content from XML file
	XMLFile.LoadFile();
	
	// make sure the parameter map is empty
	Parameters.clear();
	
	
	//loop through the XML elements and put parameters + their values into map
	
	TiXmlElement *RootNode = XMLFile.RootElement();
	
	for(TiXmlElement *XMLElement = RootNode->FirstChildElement(); XMLElement != NULL; XMLElement = XMLElement->NextSiblingElement())
	{
		
		Parameters[XMLElement->Value()] = XMLElement->GetText();
					
	}
	
	return true;
	
}


//-----------------------------------------------------------------------------
bool ConfigParser::WriteConfig(void) //write parameters into XML config file 
//-----------------------------------------------------------------------------
{
	
	
	XMLFile.SaveFile();
	return true;
	
}


//-----------------------------------------------------------------------------
std::string ConfigParser::GetParam(std::string parametername) //get parameter value
//-----------------------------------------------------------------------------
{
	
	return Parameters[parametername];
}


//-----------------------------------------------------------------------------
bool ConfigParser::SetParam(std::string parametername, std::string value) //set parameter value
//-----------------------------------------------------------------------------
{


	if (Parameters.find(parametername) == Parameters.end()) //Parameter nicht vorhanden
	{
		
		return false;
	}
	
	else {
		
		
		//change the value also in the XMLDocument Object in Memory
		
		TiXmlElement *RootNode = XMLFile.RootElement();
		TiXmlElement *ParamElement = RootNode->FirstChildElement(parametername);
		ParamElement->FirstChild()->SetValue(value);
		
		
		//change the value in the parameter map	
		Parameters[parametername] = value;
		return true;	
	}	
}

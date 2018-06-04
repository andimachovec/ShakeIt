#ifndef BOGGLELETTER_H
#define BOGGLELETTER_H


#include <string>

class BoggleLetter
{

	public:
		BoggleLetter(std::string Name);
		std::string GetName();
		int	GetOrientation();
		void SetOrientation(int Orientation);
		void SetName(std::string Name);


	private:
		std::string name;
		int orientation;

};


#endif

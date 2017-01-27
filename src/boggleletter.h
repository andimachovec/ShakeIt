#ifndef BOGGLELETTER_H
#define BOGGLELETTER_H


#include <string>

class BoggleLetter
{

	public:
		BoggleLetter(std::string Name);
		std::string GetName(void);
		int	GetOrientation(void);
		void SetOrientation(int Orientation);

	private:
		std::string name;
		int orientation;

};


#endif

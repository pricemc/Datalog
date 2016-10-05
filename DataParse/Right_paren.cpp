#include "Right_paren.h"
int r_paren(FileReader& file);

Right_paren::Right_paren()
{
}


Right_paren::~Right_paren()
{
}

int Right_paren::read(FileReader& file)
{
	file.reset();
	return r_paren(file);
}

std::string Right_paren::getName()
{
	return "RIGHT_PAREN";
}

int r_paren(FileReader& file)
{
	if (file.getChar() == ')') return 1;
	return 0;
}
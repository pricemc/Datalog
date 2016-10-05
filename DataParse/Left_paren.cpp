#include "Left_paren.h"

int l_paren(FileReader& file);

Left_paren::Left_paren()
{
}


Left_paren::~Left_paren()
{
}

int Left_paren::read(FileReader& file)
{
	file.reset();
	return l_paren(file);
}

std::string Left_paren::getName()
{
	return "LEFT_PAREN";
}

int l_paren(FileReader& file)
{
	if (file.getChar() == '(') return 1;
	return 0;
}
#include "Rules.h"


Rules::Rules()
{
}


Rules::~Rules()
{
}

int Rules::read(FileReader& file)
{
	file.reset();
	if (r(file)) return getName().length();
	return 0;
}

std::string Rules::getName()
{
	return "RULES";
}

bool Rules::r(FileReader& file)
{
	if (file.getChar() == 'R') return u(file);
	return false;
}
bool Rules::u(FileReader& file)
{
	if (file.getChar() == 'u') return l(file);
	return false;
}
bool Rules::l(FileReader& file)
{
	if (file.getChar() == 'l') return e(file);
	return false;
}
bool Rules::e(FileReader& file)
{
	if (file.getChar() == 'e') return s(file);
	return false;
}
bool Rules::s(FileReader& file)
{
	if (file.getChar() == 's') return true;
	return false;
}
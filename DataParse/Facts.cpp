#include "Facts.h"


Facts::Facts()
{
}


Facts::~Facts()
{
}
int Facts::read(FileReader& file)
{
	file.reset();
	return f(file);
}

std::string Facts::getName()
{
	return "FACTS";
}
int Facts::s(FileReader& file)
{
	if (file.getChar() == 's') return getName().length();
	return 0;
}
int Facts::t(FileReader& file)
{
	if (file.getChar() == 't') return s(file);
	return 0;
}
int Facts::c(FileReader& file)
{
	if (file.getChar() == 'c') return t(file);
	return 0;
}
int Facts::a(FileReader& file)
{
	if (file.getChar() == 'a') return c(file);
	return 0;
}

int Facts::f(FileReader& file)
{
	if (file.getChar() == 'F') return a(file);
	return 0;
}

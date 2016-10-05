#include "Schemes.h"


Schemes::Schemes()
{
}


Schemes::~Schemes()
{
}

int Schemes::read(FileReader& file)
{
	file.reset();
	if (s(file)) return getName().length();
	return 0;
}

std::string Schemes::getName()
{
	return "SCHEMES";
}

bool Schemes::s(FileReader& file)
{
	if (file.getChar() == 'S') return c(file);
	return false;
}
bool Schemes::c(FileReader& file)
{
	if (file.getChar() == 'c') return h(file);
	return false;
}
bool Schemes::h(FileReader& file)
{
	if (file.getChar() == 'h') return e(file);
	return false;
}
bool Schemes::e(FileReader& file)
{
	if (file.getChar() == 'e') return m(file);
	return false;
}
bool Schemes::m(FileReader& file)
{
	if (file.getChar() == 'm') return es(file);
	return false;
}
bool Schemes::es(FileReader& file)
{
	if (file.getChar() == 'e') return ss(file);
	return false;
}
bool Schemes::ss(FileReader& file)
{
	if (file.getChar() == 's') return true;
	return false;
}
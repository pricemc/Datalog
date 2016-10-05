#include "Colon.h"

int colon(FileReader& file);

Colon::Colon()
{
}


Colon::~Colon()
{
}

int Colon::read(FileReader& file)
{
	file.reset();
	return colon(file);
}

std::string Colon::getName()
{
	return "COLON";
}

int Colon::colon(FileReader& file)
{
	if (file.getChar() == ':') return 1;
	return 0;
}

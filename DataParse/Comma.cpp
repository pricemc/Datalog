#include "Comma.h"

Comma::Comma()
{
}


Comma::~Comma()
{
}

int Comma::read(FileReader& file)
{
	file.reset();
	if (file.getChar() == ',') return 1;
	return 0;
}

std::string Comma::getName()
{
	return "COMMA";
}
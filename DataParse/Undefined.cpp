#include "Undefined.h"


Undefined::Undefined()
{
}


Undefined::~Undefined()
{
}

int Undefined::read(FileReader& file)
{
	return 1;
}

std::string Undefined::getName()
{
	return "UNDEFINED";
}
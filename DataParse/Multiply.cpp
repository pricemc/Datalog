#include "Multiply.h"

int mult(FileReader& file);
Multiply::Multiply()
{
}


Multiply::~Multiply()
{
}


int Multiply::read(FileReader& file)
{
	file.reset();
	return mult(file);
}

std::string Multiply::getName()
{
	return "MULTIPLY";
}

int mult(FileReader& file)
{
	if (file.getChar() == '*') return 1;
	return 0;
}
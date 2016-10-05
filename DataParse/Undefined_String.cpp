#include "Undefined_String.h"


Undefined_String::Undefined_String()
{
}


Undefined_String::~Undefined_String()
{
}

int Undefined_String::read(FileReader& file)
{
	file.reset();
	if (first(file))
	{
		int number = afterFirst(file);
		if (number == 0) return 0;
		return number + 1;
	}
	return 0;
}

std::string Undefined_String::getName()
{
	return "UNDEFINED";
}

bool Undefined_String::first(FileReader& file)
{
	if (file.getChar() == '\'') return true;
	return false;
}

int Undefined_String::afterFirst(FileReader& file)
{
	char c = file.getChar();
	if (c != '\'' && c != EOF)
	{
		int number = afterFirst(file);
		return number + 1;
	}
	else if (c == '\'') return apostrophe(file);
	return 0;
}

int Undefined_String::apostrophe(FileReader& file)
{
	if (file.getChar() == '\'') return afterFirst(file) + 1;
	return 0;
}
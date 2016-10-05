#include "String.h"


String::String()
{
}


String::~String()
{
}

int String::read(FileReader& file)
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

std::string String::getName()
{
	return "STRING";
}

bool String::first(FileReader& file)
{
	if (file.getChar() == '\'') return true;
	return false;
}

int String::afterFirst(FileReader& file)
{
	char c = file.getChar();
	if (c != '\'' && c != EOF)
	{
		int number = afterFirst(file);
		if (number == 0) return 0;
		return number + 1;
	}
	else if (c == '\'') return apostrophe(file) + 1;
	return 0;
}

int String::apostrophe(FileReader& file)
{
	if (file.getChar() == '\'') return afterFirst(file);
	return 0;
}
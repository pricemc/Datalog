#include "Id.h"


Id::Id()
{
}


Id::~Id()
{
}

int Id::read(FileReader& file)
{
	file.reset();
	if(first(file))return afterFirst(file) + 1;
	return 0;
}

std::string Id::getName()
{
	return "ID";
}

bool Id::first(FileReader& file)
{
	if (isalpha(file.getChar())) return true;
	return false;
}

int Id::afterFirst(FileReader& file)
{
	char c = file.getChar();
	if (isalpha(c) || isdigit(c)) return afterFirst(file) + 1;
	return 0;
}
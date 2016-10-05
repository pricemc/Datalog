#include "Undefined_Comment.h"


Undefined_Comment::Undefined_Comment()
{
}


Undefined_Comment::~Undefined_Comment()
{
}

int Undefined_Comment::read(FileReader& file)
{
	file.reset();
	if (hash(file))
	{
		int number = whichComment(file);
		if (number == 0) return 0;
		return number + 1;
	}
	return 0;
}

std::string Undefined_Comment::getName()
{
	return "UNDEFINED";
}
bool Undefined_Comment::hash(FileReader& file)
{
	if (file.getChar() == '#') return true;
	return false;
}
int Undefined_Comment::whichComment(FileReader& file)
{
	if (file.getChar() == '|'){
		int number = block(file);
		if (number == 0) return 0;
		return number + 1;
	}
	return 0;
}

int Undefined_Comment::block(FileReader& file)
{
	char c = file.getChar();
	if (c != EOF && c != '|')
	{
		int number = block(file);
		if (number == 0) return 0;
		return number + 1;
	}
	else if (c == '|' && hash(file))
	{
		return 0;
	}
	return 1;
}
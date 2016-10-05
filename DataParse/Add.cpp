#include "Add.h"

int add(FileReader& file);
Add::Add()
{
}


Add::~Add()
{
}

int Add::read(FileReader& file)
{
	file.reset();
	return add(file);
}

std::string Add::getName()
{
	return "ADD";
}

int add(FileReader& file)
{
	if (file.getChar() == '+') return 1;
	return 0;
}
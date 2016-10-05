#include "Period.h"

int period(FileReader& file);

Period::Period()
{
}


Period::~Period()
{
}

int Period::read(FileReader& file)
{
	file.reset();
	return period(file);
}

std::string Period::getName()
{
	return "PERIOD";
}
int period(FileReader& file)
{
	if (file.getChar() == '.') return 1;
	return 0;
}
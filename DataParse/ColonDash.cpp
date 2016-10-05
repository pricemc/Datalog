#include "ColonDash.h"

int dash(FileReader& file);
int colon(FileReader& file);
ColonDash::ColonDash()
{
}


ColonDash::~ColonDash()
{
}

int ColonDash::read(FileReader& file)
{
	file.reset();
	return colon(file);
}

std::string ColonDash::getName()
{
	return "COLON_DASH";
}
int dash(FileReader& file)
{
	if (file.getChar() == '-') return 2;
	return 0;
}

int colon(FileReader& file)
{
	if (file.getChar() == ':') return dash(file);
	return 0;
}

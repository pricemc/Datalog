#include "Q_mark.h"

int mark(FileReader& file);

Q_mark::Q_mark()
{
}


Q_mark::~Q_mark()
{
}

int Q_mark::read(FileReader& file)
{
	file.reset();
	return mark(file);
}

std::string Q_mark::getName()
{
	return "Q_MARK";
}
int mark(FileReader& file)
{
	if (file.getChar() == '?') return 1;
	return 0;
}
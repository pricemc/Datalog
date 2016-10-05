#include "Queries.h"


Queries::Queries()
{
}


Queries::~Queries()
{
}

int Queries::read(FileReader& file)
{
	file.reset();
	if (q(file)) return getName().length();
	return 0;
}

std::string Queries::getName()
{
	return "QUERIES";
}

bool Queries::q(FileReader& file)
{
	if (file.getChar() == 'Q') return u(file);
	return false;
}
bool Queries::u(FileReader& file)
{
	if (file.getChar() == 'u') return e(file);
	return false;
}
bool Queries::e(FileReader& file)
{
	if (file.getChar() == 'e') return r(file);
	return false;
}
bool Queries::r(FileReader& file)
{
	if (file.getChar() == 'r') return i(file);
	return false;
}
bool Queries::i(FileReader& file)
{
	if (file.getChar() == 'i') return es(file);
	return false;
}
bool Queries::es(FileReader& file)
{
	if (file.getChar() == 'e') return s(file);
	return false;
}
bool Queries::s(FileReader& file)
{
	if (file.getChar() == 's') return true;
	return false;
}
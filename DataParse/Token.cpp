#include "Token.h"


Token::Token(std::string nameIn, std::string stringIn, int lineIn)
{
	name = nameIn;
	string = stringIn;
	line = lineIn;
}


Token::~Token()
{
}
std::string Token::getName()
{
	return name;
}
std::string Token::getString()
{
	return string;
}
int Token::getLine()
{
	return line;
}

std::string Token::toString()
{
	std::stringstream output;
	output << "(" << getName() << ",\"" << getString() << "\"," << getLine() << ")";
	return output.str();
}
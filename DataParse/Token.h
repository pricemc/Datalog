#pragma once
#include <string>
#include <sstream>
class Token
{
public:
	Token(std::string nameIn, std::string stringIn, int lineIn);
	~Token();
	std::string getName();
	std::string getString();
	int getLine();
	std::string toString();
private:
	std::string name;
	std::string string;
	int line;
};


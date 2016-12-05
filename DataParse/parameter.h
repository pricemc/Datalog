#pragma once
#include <string>
class parameter
{
public:
	parameter();
	parameter(std::string name_in);
	~parameter();
	std::string toString();
	int type();
	std::string name;
};


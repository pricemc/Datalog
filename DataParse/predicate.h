#pragma once
#include <string>
#include <deque>
#include "parameter.h"
class predicate
{
public:
	predicate(parameter id_in, std::deque<parameter*> params_in);
	~predicate();
	std::string toString();
	std::deque<parameter*> params;
	std::string info;
	void setInfo(std::string);
private:
	parameter id;
};


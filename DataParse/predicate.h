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
private:
	parameter id;
};


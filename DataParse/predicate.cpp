#include "predicate.h"


predicate::predicate(parameter id_in, std::deque<parameter*> params_in)
{
	id = id_in;
	params = params_in;
}


predicate::~predicate()
{
}


std::string predicate::toString()
{
	std::string output = id.toString();
	output += "(";
	for (int i = 0; i < params.size() - 1; i++)
		output += params[i]->toString() + ",";
	output += params.back()->toString() + ")";
	return output;
}
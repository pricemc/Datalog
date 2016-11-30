#include "rule.h"


rule::rule(predicate* head_in, std::deque<predicate*> predicates_in)
{
	head = head_in;
	predicates = predicates_in;
}


rule::~rule()
{
}


std::string rule::toString()
{
	std::string output = head->toString();
	output += " :- ";
	for (int i = 0; i < predicates.size() - 1; i++)
		output += predicates[i]->toString() + ",";
	output += predicates.back()->toString() + ".";
	return output;
}
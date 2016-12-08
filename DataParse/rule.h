#pragma once
#include "predicate.h"
#include <deque>
class rule
{
public:
	rule(predicate* head_in, std::deque<predicate*> predicates_in);
	~rule();
	std::string toString();

	predicate* head;
	std::deque<predicate*> predicates;
};


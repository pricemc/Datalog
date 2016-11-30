#pragma once
#include "predicate.h"
#include "rule.h"
#include <vector>
#include <set>
#include <sstream>
class datalogProgram
{
public:
	datalogProgram();
	~datalogProgram();
	void addScheme(predicate* add);
	void addFact(predicate* add);
	void addRule(rule* add);
	void addQueries(predicate* add);
	void addDomain(parameter* add);
	int factSize();
	std::string toString();
	std::vector<predicate*> facts;

private:
	std::vector<predicate*> schemes;
	std::vector<rule*> rules;
	std::vector<predicate*> queries;
	std::set<parameter*> domain;
};


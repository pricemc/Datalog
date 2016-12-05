#include "datalogProgram.h"
#include <iostream>

datalogProgram::datalogProgram()
{
}


datalogProgram::~datalogProgram()
{
}

void datalogProgram::addScheme(predicate* add)
{
	schemes.push_back(add);
}
void datalogProgram::addFact(predicate* add)
{
	std::cout << "here";
	facts.push_back(add);
}
void datalogProgram::addRule(rule* add)
{
	rules.push_back(add);
}
void datalogProgram::addQueries(predicate* add)
{
	queries.push_back(add);
}
void datalogProgram::addDomain(parameter* add)
{
	domain.insert(add);
}

std::string datalogProgram::toString()
{
	std::stringstream output;
	output << "Schemes(" << schemes.size() << ")\n";
	for (int i = 0; i < schemes.size(); i++)
		output << "\t" << schemes[i]->toString() << std::endl;
	output << "Facts(" << facts.size() << ")\n";
	for (int i = 0; i < facts.size(); i++)
		output << "\t" << facts[i]->toString() << std::endl;
	output << "Rules(" << rules.size() << ")\n";
	for (int i = 0; i < rules.size(); i++)
		output << "\t" << rules[i]->toString() << std::endl;
	output << "Queries(" << queries.size() << ")\n";
	for (int i = 0; i < queries.size(); i++)
		output << "\t" << queries[i]->toString() << std::endl;
	output << "Domain(" << domain.size() << ")\n";
	for (std::set<parameter*>::iterator i = domain.begin(); i != domain.end(); i++) {
		parameter* element = *i;
		output << "\t" << element->toString() << std::endl;
	}
	return output.str();
}

int datalogProgram::factSize()
{
	return facts.size();
}
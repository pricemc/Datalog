#include <iostream>
#include <vector>
#include <deque>
#include "Scanner.h"
#include "FileReader.h"
#include "Token.h"

#include "Parser.h"
#include "Relation.h"
#include "Database.h"


int main(int argc, char *argv[])
{
	//Usage Requirements
	FileReader input;
	std::string test = "Schemes:  	dc(D,C) Facts: 	dc('ralph','howard'). Rules:  Queries: 	dc('ralph', X)? 	dc('bob','bob')? 	dc(X,Y)?";
	if (argc != 2)
	{
		//use test data
		//std::cout << "usage: " << argv[0] << " <filename>\n";
		//std::cout << "Using test data instead: \n" << test << std::endl;
		input.test(test);
	}
	else {
		input.read(argv[1]);
	}
	Scanner a;
	std::deque<Token*> tokens = a.read(input);
	Parser* parser = new Parser();
	std::pair<bool, datalogProgram> output = parser->parse(tokens);

	Database db;
	db.fill(output.second);
	int j = 0; 
	stringstream dd;
	vector<int> varIndex;
	for (int i = 0; i < db.toPrint.size(); i++)
	{
		//cout << db.toPrint[i].printRelation(j,dd,varIndex);
	}
	cout << db.printResults();

	/*for (int i = 0; i < tokens.size(); i++)
	{
		std::cout << tokens[i]->getName() << std::endl;
	}*/

	/*//Datalog Parser
	Parser* parser = new Parser();
	std::pair<bool, datalogProgram> output = parser->parse(tokens);
	std::cout << ((output.first ? "Success!" : "Failure.\n" + tokens.front()->toString()));
	std::cout << std::endl;
	for (int i = 0; i < tokens.size(); i++) delete tokens[i];
	delete parser;
	std::cout << output.second.toString();

	if (!output.first) return 0;

	//Relational Database
	vector<predicate*> schemes = output.second.schemes;
	vector<predicate*> facts = output.second.facts;
	vector<predicate*> queries = output.second.queries;
	set<parameter*> domain = output.second.domain;

	Relation r;

	int i = 0;
	//while (i < schemes.size())
	{
		r.setNameSchema(schemes, i);

		for (int j = 0; j < facts.size(); j++)
		{
			if (r.name == facts.at(j)->id.name)
			{
				r.setTuples(facts, j);
			}
		}
	//	i++;
	}

	std::cout << "Relations:\n" << r.toString() << endl;

	vector<string> s = r.scheme.getMyAttributes();
	for (int i = 0; i < s.size(); i++)
	{
		for (std::set<parameter*>::iterator x = domain.begin(); x != domain.end(); x++) {
			parameter* element = *x;
			std::cout << "Select " << s[i] << " = " << element->name << ":\n" << r.select(i, element->name).toString();
		}
	}
	cout << "PASS\n";

	vector<int> z;
	for (int i = 0; i < s.size(); i++)
	{
		z.push_back(i);
		std::cout << "Project = " << ":\n" << r.project(z).toString();
	}
	z.clear();
	for (int i = s.size()-1; i >= 0; i--)
	{
		z.push_back(i);
		std::cout << "Project = " << ":\n" << r.project(z).toString();
	}
	z.clear();
	cout << "PASS\n";

	std::cout << "Rename x = y :\n" << r.rename("y", 0).toString();

	std::cout << "Rename y = old :\n" << r.rename("old", 1).toString();
	z.clear();
	cout << "PASS\n";*/


	return 0;
}
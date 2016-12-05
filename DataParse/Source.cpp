#include <iostream>
#include <vector>
#include <deque>
#include "Scanner.h"
#include "FileReader.h"
#include "Token.h"

#include "Parser.h"
#include "Relation.h"


int main(int argc, char *argv[])
{
	//Usage Requirements
	FileReader input;
	std::string test = "Schemes: i(x) \nFacts: i('j'). i('x').\nRules: i(x):-i(x). \nQueries: HasSameAddress('Snoopy',Who)?";
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

	/*for (int i = 0; i < tokens.size(); i++)
	{
		std::cout << tokens[i]->getName() << std::endl;
	}*/

	//Datalog Parser
	Parser* parser = new Parser();
	std::pair<bool, datalogProgram> output = parser->parse(tokens);
	std::cout << ((output.first ? "Success!" : "Failure.\n" + tokens.front()->toString()));
	std::cout << std::endl;
	
	//Relational Database
	vector<predicate*> schemes = output.second.schemes;
	vector<predicate*> facts = output.second.facts;
	vector<predicate*> queries = output.second.queries;

	Relation rel;

	int i = 0;
	while (i < schemes.size())
	{
		Relation r;
		r.setNameSchema(schemes, i);

		for (int j = 0; j < facts.size(); j++)
		{
			if (r.name == facts.at(j)->info)
			{
				r.setTuples(facts, j);
			}
		}
		i++;
	}

	std::cout << rel.toString();


	for (int i = 0; i < tokens.size(); i++) delete tokens[i];
	delete parser;
	std::cout << output.second.toString();
	system("pause");
	return 0;
}
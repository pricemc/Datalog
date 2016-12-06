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
	std::string test = "Schemes: people(x,y) employer(x,z) sk(i,z) i(i,z) j(z,i) Facts: j('x', 'y'). sk('x', 'y'). employer('joe','y'). employer('joe','x'). people('joe','bob'). people('jim','bob'). people('joe','jim'). employer('ralph','howard'). people('bob','bob'). Rules: employer(X,Y):- people(Y,X). employer(X,Y):- people(X,Z),employer(Z,Y). people(X,Y):- people(Y,X). Queries: people('joe','jim')? people( who, 'bob')? people('joe', anyone)? people(X,X)? people(X,Y)? employer('ralph', X)? employer('bob','bob')? employer(X,Y)?";
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
	varIndex.push_back(1);
	int x = 1;

	//each test is on the above datalog program of 4 schemes with at least (0) facts each. There are at least 10 tests that union or join each of them together.
	for (int i = 0; i < db.relations.size(); i++)
	{
		if (x == db.relations.size()) x = 0;
		cout << "Union " << db.relations[i].name << " with " << db.relations[x].name << endl;
		cout << db.relations[i].unionWith(db.relations[x]).printRelation(j, dd, varIndex) << endl;
		dd.str("");
		x++;
	}
	cout << "PASS\n\n";
	for (int i = 0; i < db.relations.size(); i++)
	{
		if (x == db.relations.size()) x = 0;
		cout << "Natural Join " << db.relations[i].name << " with " << db.relations[x].name << endl;
		cout << db.relations[i].join(db.relations[i], db.relations[x]).printRelation(j, dd, varIndex)<< endl;
		dd.str("");
		x++;
	}
	cout << "PASS\n\n";
	system("pause");
	return 0;
}
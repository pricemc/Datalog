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
	std::string test = "Schemes: A(a) B(b) DeaUoo(a,b,c,d,e) DeaVoo(a,b,c,d,e) DeaWoo(a,b,c,d,e) Facts: A('a'). B('b'). DeaWoo('a','a','a','a','b'). DeaWoo('a','b','a','a','b'). Rules: DeaWoo(A,B,C,D,E):-A(A),A(B),A(C),A(D),A(E). DeaWoo(A,B,C,D,E):-A(A),A(B),B(C),A(D),A(E). DeaWoo(A,B,C,D,E):-A(E),B(D),A(C),B(B),A(A). DeaUoo(E,D,C,B,A):-DeaWoo(A,B,C,D,E),A(B). DeaVoo(E,D,C,B,A):-DeaUoo(A,B,C,D,E),B(D). Queries: DeaUoo(A,B,C,D,E)? DeaUoo(A,B,'a',D,E)? DeaVoo(A,B,'a',D,E)? DeaUoo(A,B,'b',D,E)? DeaWoo(A,B,'a',D,Applestrudle)? DeaWoo(A,B,'a',D,E)? DeaWoo('a','a','a','a','b')?";
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
	cout << db.printResults();
	/*int j = 0; 
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
	cout << "PASS\n\n";*/
	system("pause");
	return 0;
}
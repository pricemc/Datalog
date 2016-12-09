#include <iostream>
#include <vector>
#include <deque>
#include "Scanner.h"
#include "FileReader.h"
#include "Token.h"

#include "Parser.h"
#include "Relation.h"
#include "Database.h"
#include "Graph.h"


int main(int argc, char *argv[])
{
	//Usage Requirements
	FileReader input;
	std::string test = "Schemes: A(a,b) rA(a,b) Reflexive(a,b) colB(b) Symmetric(a,b) Transitive(a,b) SymTran(a,b) Facts: A('1','2'). A('2','3'). A('3','4'). A('4','5'). A('5','6'). A('6','7'). A('7','8'). A('8','9'). A('9','10'). Rules: Symmetric(X,Y) :- A(X,Y). Symmetric(X,Y) :- Symmetric(Y,X). rA(a,b) :- A(b,a). Reflexive(X,Y) :- A(X,Z),rA(Z,Y). Transitive(X,Y) :- A(X,Y). Transitive(X,Z) :- Transitive(X,Y),Transitive(Y,Z). SymTran(X,Y) :- SymTran(Y,X). SymTran(X,Z) :- SymTran(X,Y),SymTran(Y,Z). SymTran(X,Y) :- A(Y,X). Queries: Symmetric(Q,R)? Reflexive(Q,R)? Transitive('1',P)? A('1','2')? Symmetric('2','1')? SymTran(X,Y)?";
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


	Graph graph;
	graph.createGraph(output.second.rules);
	cout << graph.printGraph();
	cout << "PASS\n\n";

	/*string current = "";
	for (int i = 0; i < output.second.rules.size(); i++)
	{
		current = "R" + i;
		graph.depthFirst(current);
	}*/

	graph.graph = graph.reverseEdges();
	cout << "Reverse:\n" << graph.printGraph();


	Database db;
	db.fill(output.second);
	db.printResults();
	//cout << db.printResults();
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
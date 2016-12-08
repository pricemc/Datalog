#pragma once
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Relation.h"
#include "rule.h"
#include "predicate.h"
#include "datalogProgram.h"

using namespace std;

class Database {
public:
	Database();
	virtual ~Database();

	vector<Relation> relations;
	vector<Relation> toPrint;

	vector<Relation> newFacts;

	vector<predicate*> schemes;
	vector<predicate*> facts;
	vector<predicate*> queries;
	vector<rule*> rules;
	int numPass;


	void addRelation(Relation);

	void fill(datalogProgram&);

	void evalQueries(vector<predicate*>&);

	void evalQueries(deque<predicate*>&);
	void evalQueries(deque<predicate*>& currQ, bool addNewFacts);

	string printResults();
	string printParams(vector<int>&, vector<string>&, bool, int, stringstream&);

	void doRules(vector<rule*>&);

	void evalRules(vector<rule*>&);
	void evalRulesNewFacts(Relation&, Relation&, Relation&, Relation&, Relation&, Relation&, size_t);

	int getSize(); //returns total num of tuples

	Relation find(string&);

	void checkDupSchemes(vector<Relation>&);

	void removeDupSchemes(Relation&, vector<size_t>&);

	bool contains(string&, vector<string>&);
};
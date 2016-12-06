#pragma once
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Relation.h"
#include "predicate.h"

using namespace std;

class Database {
public:
	Database();
	virtual ~Database();

	vector<Relation> relations, toPrint;

	vector<predicate*> schemes;
	vector<predicate*> facts;
	vector<predicate*> queries;


	void addRelation(Relation);

	void fill(vector<predicate*>&, vector<predicate*>&, vector<predicate*>&);

	void evalQueries(vector<predicate*>&);

	string printResults();
	string printParams(vector<size_t>&, vector<string>&, bool, size_t, stringstream&);

};
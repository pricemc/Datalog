#pragma once
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include "Scheme.h"
#include "Tuple.h"
#include "rule.h"
#include "predicate.h"

using namespace std;

class Relation {
public:
	Relation();
	virtual ~Relation();

	string name;
	Scheme scheme;
	set<Tuple> myTuples;
	vector<predicate*> mySchemes;
	vector<predicate*> myFacts;
	vector<predicate*> myQueries;

	Relation select(int, string);

	Relation select(int, int);

	Relation project(vector<int>&);

	void rename(string, int);

	void setNameSchema(vector<predicate*>&, int);

	void setTuples(vector<predicate*>&, int);

	void setName(vector<predicate*>&, int);

	void setName(deque<predicate*>&, int);

	Relation evalParams(vector<predicate*>&, int, Relation);

	Relation evalParams(deque<predicate*>&, int, Relation);
	void evalParamID(Relation&, Relation&, int&, int&, int&,
		vector<string>&, vector<int>&, bool);
	void thereIsADuplicate(Relation&, Relation&, int&, int&, int&,
		vector<string>&, vector<int>&, bool);

	int isThereAnother(string, deque<parameter*>, int);

	string printRelation(int, stringstream& out, vector<int>&);

	Relation project(vector<parameter*>&);
	Relation project(deque<parameter*>&);

	Relation unionWith(Relation);

	Relation join(Relation, Relation);

	Scheme join(Scheme, Scheme);

	Tuple join(Scheme, Scheme, Tuple, Tuple);

	bool joinable(Scheme&, Scheme&, Tuple&, Tuple&);

	int getNumTuples();

};

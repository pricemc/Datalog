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

	Relation select(size_t, string);

	Relation select(size_t, size_t);

	Relation project(vector<int>&);

	Relation rename(string, size_t);

	void setNameSchema(vector<predicate*>&, size_t);

	void setTuples(vector<predicate*>&, size_t);

	void setName(vector<predicate*>&, size_t);

	Relation evalParams(vector<predicate*>&, size_t, Relation);
	void evalParamID(Relation&, Relation&, size_t&, size_t&, size_t&,
		vector<string>&, vector<int>&, bool);
	void thereIsADuplicate(Relation&, Relation&, size_t&, size_t&, size_t&,
		vector<string>&, vector<int>&, bool);

	size_t isThereAnother(string, deque<parameter*>, size_t);

	std::string toString();
	void printRelation(size_t, ofstream&, vector<size_t>&);

};

#pragma once
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class Tuple : public vector<string>
{
public:
	Tuple();
	virtual ~Tuple();

	std::string toString(vector<string>&, vector<size_t>&);
	void printTuple(ofstream&, vector<string>&, vector<size_t>&);
};

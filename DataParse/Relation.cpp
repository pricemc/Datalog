#include "Relation.h"

using namespace std;

Relation::Relation()
{
}

Relation::~Relation()
{
}


Relation Relation::select(size_t index, string value)
{
	Relation r;
	r.name = name;
	r.scheme = scheme;
	set<Tuple>::iterator it;

	for (it = myTuples.begin(); it != myTuples.end(); it++)
	{
		Tuple temp;
		temp = *it;

		if (temp.at(index) == value)
		{
			r.myTuples.insert(temp);
		}
	}

	return r;
}

Relation Relation::select(size_t index1, size_t index2)
{
	Relation r;
	r.name = name;
	r.scheme = scheme;
	set<Tuple>::iterator it;

	for (it = myTuples.begin(); it != myTuples.end(); it++)
	{
		Tuple temp;
		temp = *it;

		if (temp.at(index1) == temp.at(index2))
		{
			r.myTuples.insert(temp);
		}
	}

	return r;
}

Relation Relation::project(vector<int>& myIndicies)
{
	Relation r;
	r.name = name;
	r.scheme = scheme;
	set<Tuple>::iterator it;
	Tuple projected;
	int toProject;

	for (it = myTuples.begin(); it != myTuples.end(); it++)
	{
		Tuple temp;
		temp = *it;

		for (size_t i = 0; i < myIndicies.size(); i++)
		{
			toProject = myIndicies.at(i);
			projected.push_back(temp.at(toProject));
		}

		r.myTuples.insert(projected);
		projected.clear();
	}

	return r;
}

void Relation::rename(string s, size_t j)
{
	scheme.myAttributes.at(j) = s;
}

void Relation::setNameSchema(vector<predicate*>& s, size_t i)
{
	mySchemes = s;
	size_t index = i;
	size_t j = 0;
	vector<string> schema;

	name = mySchemes.at(index)->info;

	while (j < mySchemes.at(index)->params.size())
	{
		scheme.myAttributes.push_back(mySchemes.at(index)->params.at(j)->name);
		j++;
	}
}

void Relation::setTuples(vector<predicate*>& facts, size_t i)
{
	myFacts = facts;
	size_t index = i;
	size_t j = 0;
	Tuple t;

	while (j < myFacts.at(index)->params.size())
	{
		t.push_back(myFacts.at(index)->params.at(j)->name);
		j++;
	}

	myTuples.insert(t);
}

void Relation::setName(vector<predicate*>& q, size_t i)
{
	myQueries = q;
	size_t index = i;

	name = myQueries.at(index)->info;
}

Relation Relation::evalParams(vector<predicate*>& q, size_t i, Relation source)
{
	size_t index = i;
	size_t j = 0;
	Relation two, three;
	vector<int> toProject;
	vector<size_t> duplicateParams;
	vector<string> ids;
	size_t duplicateIndex;
	vector<string> alreadyProjected;
	bool toAdd;

	while (j < myQueries.at(index)->params.size())
	{
		toAdd = true;

		if (myQueries.at(index)->params.at(j)->type() == 0)
		{
			if (two.name == "") //if relation two hasn't been edited use the source
			{
				two = source.select(j, myQueries.at(index)->params.at(j)->name);
				j++;
			}
			else //relation two has been edited so continue to edit it
			{
				two = two.select(j, myQueries.at(index)->params.at(j)->name);
				j++;
			}
		}
		else //type == ID so project?
		{
			evalParamID(source, two, index, j, duplicateIndex, alreadyProjected, toProject, toAdd);
		}
	}//done evaluating a query

	if (toProject.size() > 0)
	{
		if (two.name == "") {
			three = source.project(toProject);
		}
		else {
			three = two.project(toProject);
		}
		return three;
	}
	else {
		return two;
	}
}

void Relation::evalParamID(Relation& source, Relation& two,
	size_t& index, size_t& j, size_t& duplicateIndex,
	vector<string>& alreadyProjected, vector<int>& toProject, bool toAdd) {

	source.rename(myQueries.at(index)->params.at(j)->name, j);
	if (two.name != "") {
		two.rename(myQueries.at(index)->params.at(j)->name, j);
	}

	duplicateIndex = isThereAnother(myQueries.at(index)->params.at(j)->name,
		myQueries.at(index)->params, j);

	if (duplicateIndex != -1) {
		thereIsADuplicate(source, two, index, j, duplicateIndex, alreadyProjected, toProject, toAdd);
	}
	else {
		for (size_t y = 0; y < alreadyProjected.size(); y++) {
			if (myQueries.at(index)->params.at(j)->name
				== alreadyProjected.at(y)) {
				toAdd = false;
				break;
			}
		}
		if (toAdd == true) {
			toProject.push_back(j);
		}
		j++;
	}
}

void Relation::thereIsADuplicate(Relation& source, Relation& two,
	size_t& index, size_t& j, size_t& duplicateIndex,
	vector<string>& alreadyProjected, vector<int>& toProject, bool toAdd) {

	if (two.name == "") {
		two = source.select(j, duplicateIndex);
	}
	else {
		two = two.select(j, duplicateIndex);
	}

	for (size_t y = 0; y < alreadyProjected.size(); y++) {
		if (myQueries.at(index)->params.at(j)->name
			== alreadyProjected.at(y)) {
			toAdd = false;
			break;
		}
	}
	if (toAdd == true) {
		toProject.push_back(j);
		alreadyProjected.push_back(
			myQueries.at(index)->params.at(j)->name);
	}
	j++;
}

size_t Relation::isThereAnother(string id, deque<parameter*> p, size_t j)
{
	size_t duplicateIndex = -1;

	if (j + 1 < p.size())
	{
		for (size_t i = j + 1; i < p.size(); i++)
		{
			if (duplicateIndex == -1)
			{
				if (p.at(i)->type() == 1)
				{
					duplicateIndex = i;
					break;
				}
			}
		}
	}
	else
	{
		duplicateIndex = -1;
	}

	return duplicateIndex;
}

void Relation::printRelation(size_t i, ofstream& out, vector<size_t>& varIndex)
{
	set<Tuple>::iterator it;
	vector<string> myAttributes = scheme.getMyAttributes();

	if (myTuples.size() < 1)//empty relation
	{
		out << "No" << endl;
	}
	else
	{
		out << "Yes(" << myTuples.size() << ")" << endl;
	}

	for (it = myTuples.begin(); it != myTuples.end(); it++)
	{
		Tuple temp;
		temp = *it;

		temp.printTuple(out, myAttributes, varIndex);
	}
}
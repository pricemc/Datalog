#include "Database.h"

using namespace std;

Database::Database()
{
}

Database::~Database()
{
}

void Database::addRelation(Relation r)
{
	relations.push_back(r);
}

void Database::fill(datalogProgram& dp)
{
	schemes = dp.schemes;
	facts = dp.facts;
	queries = dp.queries;
	rules = dp.rules;
	int i = 0;
	int j = 0;

	while (i < schemes.size())
	{
		Relation r;
		r.setNameSchema(dp.schemes, i);

		for (j = 0; j < facts.size(); j++)
		{
			if (r.name == facts.at(j)->id.name)
			{
				r.setTuples(dp.facts, j);
			}
		}

		addRelation(r);
		i++;
	}

	doRules(rules);

	evalQueries(dp.queries);
}

void Database::evalQueries(vector<predicate*>& q)
{
	int i = 0;
	Relation temp, relToAdd;

	while (i < queries.size())
	{
		Relation r;
		r.setName(q, i);

		for (int j = 0; j < relations.size(); j++)
		{
			if (r.name == relations.at(j).name)
			{
				temp = relations.at(j);
			}
		}

		relToAdd = r.evalParams(q, i, temp);
		toPrint.push_back(relToAdd);
		i++;
	}
}

void Database::evalQueries(deque<predicate*>& q)
{
	int i = 0;
	Relation temp, relToAdd;

	while (i < q.size())
	{
		Relation r;
		r.setName(q, i);

		for (int j = 0; j < relations.size(); j++)
		{
			if (r.name == relations.at(j).name)
			{
				temp = relations.at(j);
			}
		}

		relToAdd = r.evalParams(q, i, temp);
		toPrint.push_back(relToAdd);
		i++;
	}
}

void Database::evalQueries(deque<predicate*>& currQ, bool addNewFacts)//q
{
	size_t i = 0;
	Relation temp, relToAdd;

	while (i < currQ.size())
	{
		Relation r;
		r.setName(currQ, i);

		for (size_t j = 0; j < relations.size(); j++)
		{
			if (r.name == relations.at(j).name)
			{
				temp = relations.at(j);
				break;
			}
		}

		if (!addNewFacts)
		{
			relToAdd = r.evalParams(currQ, i, temp);
			toPrint.push_back(relToAdd);
			i++;
		}
		else
		{
			relToAdd = r.evalParams(currQ, i, temp);
			newFacts.push_back(relToAdd);
			i++;
		}

	}
}

string Database::printResults()
{
	//original results lab 3pt2
	stringstream output;
	vector<int> varIndex;
	vector<string> variablesAlreadytoBePrinted;
	bool toAdd = false;

	output << "Schemes populated after " << numPass << " passes through the Rules." << endl;

	for (int i = 0; i < queries.size(); i++)
	{
		output << queries.at(i)->id.name << "(";

		printParams(varIndex, variablesAlreadytoBePrinted, toAdd, i, output);

		output << ")? ";

		toPrint.at(i).printRelation(i, output, varIndex);
		varIndex.clear();
		variablesAlreadytoBePrinted.clear();
	}


	return output.str();
}



string Database::printParams(vector<int>& varIndex, vector<string>& variablesAlreadytoBePrinted, bool toAdd, int i, stringstream& output) {
	for (int j = 0; j < queries.at(i)->params.size(); j++)
	{
		output << queries.at(i)->params.at(j)->toString();

		if (j < (queries.at(i)->params.size() - 1))
		{
			output << ",";
		}

		if (queries.at(i)->params.at(j)->type() == 1)
		{
			toAdd = true;

			if (varIndex.size() < 1)
			{
				varIndex.push_back(j);
				variablesAlreadytoBePrinted.push_back(queries.at(i)->params.at(j)->name);
			}
			else
			{
				for (int y = 0; y < variablesAlreadytoBePrinted.size(); y++)
				{
					if (queries.at(i)->params.at(j)->name == variablesAlreadytoBePrinted.at(y))
					{
						toAdd = false;
						break;
					}
				}
				if (toAdd == true)
				{
					varIndex.push_back(j);
					variablesAlreadytoBePrinted.push_back(queries.at(i)->params.at(j)->name);
				}
			}
		}
	}
	return output.str();
}

int Database::getSize()
{
	//gets total num of tuples
	int size = 0;

	for (size_t i = 0; i < relations.size(); i++)
	{
		size += relations.at(i).getNumTuples();
	}
	return size;
}

void Database::doRules(vector<rule*>& rules)
{
	int sizeBefore, sizeAfter, passes;
	bool keepGoing = true;

	sizeBefore = sizeAfter = passes = 0;

	while (keepGoing)
	{
		sizeBefore = getSize();
		evalRules(rules);
		passes++;
		sizeAfter = getSize();
		if (sizeBefore != sizeAfter)
		{
			keepGoing = true;
		}
		else
		{
			keepGoing = false;
		}

	}

	numPass = passes;
}

void Database::evalRules(vector<rule*>& rules)
{
	Relation one, two, three, four, clear;
	Relation projected, unioned, toUnion;

	for (size_t i = 0; i < rules.size(); i++)
	{
		one = two = three = four = clear;
		newFacts.clear();

		evalQueries(rules[i]->predicates, true);

		checkDupSchemes(newFacts);

		if (newFacts.size() < 1) //no new facts
		{
			//do nothing
		}
		else if (newFacts.size() == 1)//only one new fact
		{
			projected = newFacts.at(0).project(rules[i]->head->params);
			toUnion = find(rules[i]->head->id.name);
			unioned = projected.unionWith(toUnion);
			relations.push_back(unioned);
		}
		else //two or more new facts
		{
			evalRulesNewFacts(one, two, three, projected, unioned, toUnion, i);
		}
	}
}

void Database::evalRulesNewFacts(Relation& one, Relation& two, Relation& three,
	Relation& projected, Relation& unioned, Relation& toUnion, size_t i) {

	for (size_t j = 0; j < newFacts.size(); j++)
	{
		Relation temp1 = newFacts.at(j);
		if (one.myTuples.size() == 0)
		{
			if (j < newFacts.size() - 1)
			{
				j++;
				Relation temp2 = newFacts.at(j);

				one = one.join(temp1, temp2);

				if (j == newFacts.size() - 1)
				{
					projected = one.project(rules.at(i)->head->params);
					toUnion = find(rules.at(i)->head->id.name);
					unioned = projected.unionWith(toUnion);
					relations.push_back(unioned);
				}
			}
			else
			{
				two = two.join(one, temp1);
				projected = two.project(rules.at(i)->head->params);
				toUnion = find(rules.at(i)->head->id.name);
				unioned = projected.unionWith(toUnion);
				relations.push_back(unioned);
			}
		}
		else
		{
			three = three.join(one, temp1);
			one = three;
			if (j == newFacts.size() - 1)
			{
				projected = one.project(rules.at(i)->head->params);
				toUnion = find(rules.at(i)->head->id.name);
				unioned = projected.unionWith(toUnion);
				relations.push_back(unioned);
			}
		}
	}
}

void Database::checkDupSchemes(vector<Relation>& r)
{
	string currAttribute;

	for (size_t i = 0; i < r.size(); i++)
	{
		Scheme newScheme;
		Relation curr = r.at(i);
		Scheme currScheme = r.at(i).scheme;

		if (currScheme.myAttributes.size() > 1)
		{
			for (size_t j = 0; j < currScheme.myAttributes.size(); j++)
			{
				currAttribute = currScheme.myAttributes.at(j);

				if (contains(currAttribute, newScheme.myAttributes) == false)
				{
					newScheme.myAttributes.push_back(currAttribute);
				}
			}
			r.at(i).scheme = newScheme;
		}
	}
}

Relation Database::find(string& n)
{
	Relation temp;

	for (size_t i = 0; i < relations.size(); i++)
	{
		if (relations.at(i).name == n)
		{
			temp = relations.at(i);
			relations.erase(relations.begin() + i);
			return temp;
		}
	}

	return temp;
}

bool Database::contains(string& curr, vector<string>& currAttributes)
{
	for (size_t i = 0; i < currAttributes.size(); i++)
	{
		string temp = currAttributes.at(i);
		if (temp == curr)
		{
			return true;
		}
	}
	return false;
}

void Database::removeDupSchemes(Relation& r, vector<size_t>& removeIndex)
{
	Scheme newScheme;
	bool toRemove;

	for (size_t i = 0; i < r.scheme.myAttributes.size(); i++)
	{
		toRemove = false;

		for (size_t j = 0; j < removeIndex.size(); j++)
		{
			if (removeIndex.at(j) == i)
			{
				toRemove = true;
				break;
			}
		}
		if (!toRemove)
		{
			newScheme.myAttributes.push_back(r.scheme.myAttributes.at(i));
		}
	}
	r.scheme = newScheme;
}
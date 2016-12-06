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

void Database::fill(vector<predicate*>& s, vector<predicate*>& f, vector<predicate*>& q)
{
	schemes = s;
	facts = f;
	queries = q;
	size_t i = 0;
	size_t j = 0;

	while (i < schemes.size())
	{
		Relation r;
		r.setNameSchema(s, i);

		for (j = 0; j < facts.size(); j++)
		{
			if (r.name == facts.at(j)->id.name)
			{
				r.setTuples(f, j);
			}
		}

		addRelation(r);
		i++;
	}
	evalQueries(q);
}

void Database::evalQueries(vector<predicate*>& q)
{
	size_t i = 0;
	Relation temp, relToAdd;

	while (i < queries.size())
	{
		Relation r;
		r.setName(q, i);

		for (size_t j = 0; j < relations.size(); j++)
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

string Database::printResults()
{
	stringstream out;
	vector<size_t> varIndex;
	vector<string> variablesAlreadytoBePrinted;
	bool toAdd;

	for (size_t i = 0; i < queries.size(); i++)
	{
		out << queries.at(i)->toString();

		printParams(varIndex, variablesAlreadytoBePrinted, toAdd, i, out);

		out << ")? ";

		toPrint.at(i).printRelation(i, out, varIndex);
		varIndex.clear();
		variablesAlreadytoBePrinted.clear();
	}
	return out.str();
}



string Database::printParams(vector<size_t>& varIndex, vector<string>& variablesAlreadytoBePrinted, bool toAdd, size_t i, stringstream& out) {
	for (size_t j = 0; j < queries.at(i)->params.size(); j++)
	{
		out << queries.at(i)->params.at(j)->toString();

		if (j < (queries.at(i)->params.size() - 1))
		{
			out << ",";
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
				for (size_t y = 0; y < variablesAlreadytoBePrinted.size(); y++)
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
	return out.str();
}

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

string Database::printResults()
{
	stringstream output;
	vector<int> varIndex;
	vector<string> variablesAlreadytoBePrinted;
	bool toAdd = false;

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

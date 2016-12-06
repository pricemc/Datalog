#include "Tuple.h"

using namespace std;

Tuple::Tuple() {
	// TODO Auto-generated constructor stub

}

Tuple::~Tuple() {
	// TODO Auto-generated destructor stub
}

std::string Tuple::toString(vector<string>& myAttributes, vector<int>& varIndex)
{
	stringstream output;
	if (varIndex.size() > 0)
	{
		for (int i = 0; i < size(); i++)
		{
			if (i < size() - 1)
			{
				if (i == 0)
				{
					output << "  " << myAttributes.at(i) << "=" << at(i) << ", ";
				}
				else
				{
					output << myAttributes.at(i) << "=" << at(i) << ", ";
				}
			}
			else
			{
				if (i == 0)
				{
					output << "  " << myAttributes.at(i) << "=" << at(i);
				}
				else
				{
					output << myAttributes.at(i) << "=" << at(i);
				}
			}
		}
		output << endl;
	}
	
	return output.str();
}

string Tuple::printTuple(stringstream& out, vector<string>& myAttributes, vector<int>& varIndex)
{
	//if (varIndex.size() > 0) //there are variables to print
	{
		if (varIndex.size() < 2)
		{
			for (int i = 0; i < size(); i++)
			{
				out << "  " << myAttributes.at(varIndex.at(i)) << "='" << at(i) << "'" << endl;
			}
		}
		else
		{
			for (int i = 0; i < size(); i++)
			{
				if (i < size() - 1)
				{
					if (i == 0)
					{
						out << "  " << myAttributes.at(varIndex.at(i)) << "='" << at(i) << "', ";
					}
					else
					{
						out << myAttributes.at(varIndex.at(i)) << "='" << at(i) << "', ";
					}
				}
				else
				{
					if (i == 0)
					{
						out << "  " << myAttributes.at(varIndex.at(i)) << "='" << at(i) << "'" << endl;
					}
					else
					{
						out << myAttributes.at(varIndex.at(i)) << "='" << at(i) << "'" << endl;
					}
				}
			}
		}
	}
	return out.str();
}
#include "Tuple.h"

using namespace std;

Tuple::Tuple() {
	// TODO Auto-generated constructor stub

}

Tuple::~Tuple() {
	// TODO Auto-generated destructor stub
}

std::string Tuple::toString(vector<string>& myAttributes, vector<size_t>& varIndex)
{
	stringstream output;
	for (size_t i = 0; i < size(); i++)
	{
		if (i < size() - 1)
		{
			if (i == 0)
			{
				output << "\t" << myAttributes.at(i) << "=" << at(i) << ", ";
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
				output << "\t" << myAttributes.at(i) << "=" << at(i);
			}
			else
			{
				output << myAttributes.at(i) << "=" << at(i);
			}
		}
	}
	
	return output.str();
}

void Tuple::printTuple(ofstream& out, vector<string>& myAttributes, vector<size_t>& varIndex)
{
	if (varIndex.size() > 0) //there are variables to print
	{
		if (varIndex.size() < 2)
		{
			for (size_t i = 0; i < size(); i++)
			{
				out << "  " << myAttributes.at(varIndex.at(i)) << "='" << at(i) << "'" << endl;
			}
		}
		else
		{
			for (size_t i = 0; i < size(); i++)
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
}
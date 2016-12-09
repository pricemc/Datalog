#include "Graph.h"
#include <iostream>
Graph::Graph()
{
}


Graph::~Graph()
{
}

void Graph::createGraph(vector<rule*>& myRules)
{

	for (size_t i = 0; i < myRules.size(); i++)
	{
		string currR = myRules.at(i)->head->id.name;
		Node n;
		int curr = i;
		string key = "R" + convertInt(curr);
		set<string> currSet;

		for (size_t z = 0; z < myRules.at(i)->predicates.size(); z++)
		{
			string currPred = myRules.at(i)->predicates.at(z)->id.name;
			string key2;

			for (size_t j = 0; j < myRules.size(); j++)
			{
				int curr = j;
				string ruleHead = myRules.at(j)->head->id.name;

				if (currPred == ruleHead)
				{
					key2 = "R" + convertInt(curr);
					currSet.insert(key2);
				}
			}
		}

		n.adjacentNodes = currSet;
		graph[key] = n;
	}
}


string Graph::printGraph()
{
	stringstream out;
	map<string, Node>::iterator it;
	set<string>::iterator iter;

	out << "Dependency Graph" << endl;

	for (it = graph.begin(); it != graph.end(); it++)
	{
		out << it->first << ":";

		Node n = it->second;
		set<string> curr = n.adjacentNodes;
		bool first = true;
		for (iter = curr.begin(); iter != curr.end(); iter++)
		{
			string curr = *iter;
			if (first)
			{
				first = false;
			}
			else out << ",";
			out << curr;
		}
		out << endl;
	}
	return out.str();
}

void Graph::computePostOrder()
{
	map<string,Node> reverse = reverseEdges();
	int i = 0;

	string first = "R0";
	computePostOrder(first, reverse, i);
}

void Graph::computePostOrder(string& startNode, map<string,Node>& reverse, int& order)
{
	if (reverse[startNode].adjacentNodes.size() == 0 && reverse[startNode].visited == false)
	{
		reverse[startNode].postOrder = order;
		reverse[startNode].visited = true;
		order++;
		return;
	}
	set<string>::iterator it;
	for (it = reverse[startNode].adjacentNodes.begin(); it != reverse[startNode].adjacentNodes.end(); it++)
	{
		std::cout << "here";
		string first = *it;
		computePostOrder(first, reverse, order);
	}
}

map<string, Node> Graph::reverseEdges()
{
	map<string, Node> newg;
	map<string, Node>::iterator it;
	for (it = graph.begin(); it != graph.end(); it++)
	{
		string curr = it->first;
		Node n = it->second;
		set<string>::iterator nodes;
		for (nodes = (n.adjacentNodes).begin(); nodes != n.adjacentNodes.end(); nodes++)
		{
			string key = *nodes;
			newg[key] = n;
			newg[key].adjacentNodes.clear();
			newg[key].adjacentNodes.insert(curr);
		}
	}
	if (newg.size() < graph.size())
	{
		for (it = graph.begin(); it != graph.end(); it++)
			if (newg.find(it->first) == newg.end())
			{
				newg[it->first] = it->second;
				newg[it->first].adjacentNodes.clear();
			}
	}
	return newg;
}

void Graph::depthFirst(string& currQ)
{
	set<string>::iterator iter;

	Node q = graph[currQ];
	set<string> currAdj = q.adjacentNodes;
	graph[currQ].visited = true;

	if (!currAdj.empty())
	{
		for (iter = currAdj.begin(); iter != currAdj.end(); iter++)
		{
			string dependsOn = *iter;
			if (dependsOn != "" && graph[dependsOn].visited == false)
			{
				depthFirst(dependsOn);
			}
		}
		graph[currQ].postOrder = postCntr;
		postCntr++;
	}
	else
	{
		graph[currQ].postOrder = postCntr;
		postCntr++;
	}
}

string Graph::printPostNums()
{
	stringstream out;
	map<string, Node>::iterator it;

	out << "Postorder Numbers" << endl;

	for (it = graph.begin(); it != graph.end(); it++)
	{
		Node n = it->second;
		if (n.postOrder != 3000000)
		{
			out << "    " << it->first << ": " << n.postOrder << endl;
		}
	}

	out << endl;
	return out.str();
}


string Graph::printRuleOrder(string currQ)
{
	map<string, Node>::iterator it;
	stringstream out;
	int endCount = graph[currQ].postOrder;
	int count = 1;

	out << "  Rule Evaluation Order" << endl;

	while (count < endCount)
	{
		for (it = graph.begin(); it != graph.end(); it++)
		{
			string curr = it->first;
			Node n = it->second;

			if (curr[0] == 'Q')
			{

			}
			else
			{
				if (n.postOrder == count)
				{
					out << "    " << curr << endl;
					count++;
				}
			}
		}
	}

	out << endl;
	return out.str();
}


string Graph::printBackwardEdges()
{
	stringstream out;
	out << "  Backward Edges" << endl;

	map<string, Node>::iterator it;

	for (it = graph.begin(); it != graph.end(); it++)
	{
		string curr = it->first;
		Node n = it->second;
		int currPostOrder = n.postOrder;

		if (curr[0] == 'R')
		{
			out << continuePrintingBackwardEdges(curr, n, currPostOrder);
		}
	}

	out << endl;
	return out.str();;
}


string Graph::continuePrintingBackwardEdges(string& curr, Node& n, int& currPostOrder) {
	int counter = 1;
	bool startedPrinting = false;
	bool closedLine = false;
	set<string>::iterator iter;
	stringstream out;

	for (iter = n.adjacentNodes.begin(); iter != n.adjacentNodes.end(); iter++)
	{
		string adjacent = *iter;
		if (graph[adjacent].postOrder != 3000000)
		{
			int adjPostOrder = graph[adjacent].postOrder;

			if (currPostOrder <= adjPostOrder)
			{
				if (startedPrinting == false)
				{
					if (counter == n.adjacentNodes.size())
					{
						out << "    " << curr << ": " << adjacent << endl;
						closedLine = true;
						startedPrinting = true;
					}
					else
					{
						out << "    " << curr << ": " << adjacent;
						closedLine = false;
						startedPrinting = true;
					}
				}
				else
				{
					out << " " << adjacent;
				}
			}
		}
		counter++;
	}
	if (startedPrinting == true && closedLine == false)
	{
		out << endl;
	}
	return out.str();
}

void Graph::reset()
{
	map<string, Node>::iterator it;

	for (it = graph.begin(); it != graph.end(); it++)
	{
		string curr = it->first;
		graph[curr].postOrder = 3000000;
		graph[curr].visited = false;
	}

	postCntr = 1;
}

string Graph::convertInt(int number)
{
	stringstream ss;
	ss << number;
	return ss.str();
}
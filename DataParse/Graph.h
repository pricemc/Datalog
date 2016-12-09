#pragma once
#include <string>
#include <map>
#include <vector>
#include <set>
#include <sstream>

#include "predicate.h"
#include "rule.h"

using namespace std;
#ifndef NODE_H_
#define NODE_H_
struct Node {

	set<string> adjacentNodes;
	bool visited;
	int postOrder;

	Node()
	{
		visited = false;
		postOrder = 3000000;
	}
};

#endif

class Graph
{


public:
	Graph();
	~Graph();

	map<string, Node> graph;
	int postCntr;

	void createGraph(vector<rule*>&);
	string printGraph();
	void computePostOrder();
	void computePostOrder(string& startNode, map<string,Node>&, int&);
	map<string, Node> reverseEdges();


	void depthFirst(string& currQ);

	string printPostNums();
	string printRuleOrder(string);
	string printBackwardEdges();
	string continuePrintingBackwardEdges(string&, Node&, int&);
	void reset();
	string convertInt(int);
};


#include <cstring>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>

using namespace std;

class Graph {
public:
	Graph();
	~Graph() { };
	void srcGraphInit();
	void RunTest();
	set<INode*> nodes;
	Environment input;
	INode* entry;
	INode* exit;
};
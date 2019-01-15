#include <cstring>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Graph.h"

using namespace std;

// public
Graph::Graph() {
	entry = NULL;
	exit = NULL;
}

void Graph::srcGraphInit() {
	//セットでまとめられないため一時的処置		
	AssignNode XA, YB, Z0, ZZX, ZZY, ZZY2;
	BranchNode X10, Z20;
	FuncNode print;

	/*
	 * set variables
	 */ 
	// XA
	Aconst* A = new Aconst(Ainit);
	// YB
	Aconst* B = new Aconst(Binit);
	// Z0
	Aconst* r3 = new Aconst(Zinit);
	// X10
	Avar* l4 = new Avar("X", Ainit);
	Bless* X4 = new Bless(l4, 10);
	// ZZX
	Avar* lplus5 = new Avar("Z", 0);
	Avar* rplus5 = new Avar("X", Ainit);
	Aplus* r5 = new Aplus(lplus5, rplus5);
	// ZZY
	Avar* lplus6 = new Avar("Z", 0);
	Avar* rplus6 = new Avar("Y", Binit);
	Aplus* r6 = new Aplus(lplus6, rplus6);
	// Z20
	Avar* l7 = new Avar("Z", 0);
	Bless* Z7 = new Bless(l7, 20);
	// ZZY2
	Avar* lplus8 = new Avar("Z", 0);
	Avar* rplus8 = new Avar("Y", Ainit);
	Aplus* r8 = new Aplus(lplus8, rplus8);

	initANode(&nodes.aNodes[0], 1, "X", A, &nodes.aNodes[1]);
	nodes.aNodes[0].setEnv(0, 0, 0);
	initANode(&nodes.aNodes[1], 2, "Y", B, &nodes.aNodes[2]);
	initANode(&nodes.aNodes[2], 3, "Z", r3, &nodes.bNodes[0]);
	initBNode(&nodes.bNodes[0], 4, X4, &nodes.aNodes[3], &nodes.aNodes[4]);
	initANode(&nodes.aNodes[3], 5, "Z", r5, &nodes.aNodes[4]);
	initANode(&nodes.aNodes[4], 6, "Z", r6, &nodes.bNodes[1]);
	initBNode(&nodes.bNodes[1], 7, Z7, &nodes.aNodes[5], &nodes.fNodes[0]);
	initANode(&nodes.aNodes[5], 8, "Z", r8, &nodes.bNodes[1]);
	nodes.fNodes[0].setLabel(9);
	nodes.fNodes[0].setNext(NULL);

	entry = &nodes.aNodes[0];
	exit = &nodes.fNodes[0];

	/*
	 * print src code
	 */ 

	printNodes(entry);
}

void Graph::runTest() {
	testGraph(entry);
}

INode* Graph::getEntry() {
	return entry;
}


// private
void Graph::initANode(AssignNode* target, int label, string vname, Arithmetic* var, INode* nextNode) {
	target->setLabel(label);
	target->setValue(vname, var);
	target->setNext(nextNode);
}

void Graph::initBNode(BranchNode* target, int label, ImpBool* direction, INode* tNode, INode* fNode) {
	target->setLabel(label);
	target->setDirect(direction);
	target->setNext(tNode, fNode);
}

void Graph::setNodes(AssignNode* assignNodes, BranchNode* branchNodes, FuncNode* funcNodes) {
	for (int i = 0; i < aLength; i++) {
		nodes.aNodes[i] = assignNodes[i];
	}
	for (int i = 0; i < bLength; i++) {
		cout << &assignNodes[i] << endl;
		nodes.bNodes[i] = branchNodes[i];
		cout << &nodes.bNodes[i] << endl;
	}
	for (int i = 0; i < fLength; ++i) {
		nodes.fNodes[i] = funcNodes[i];
	}
	
	return;
}	

void Graph::testGraph(INode* node) {
	// if (node->getLabel() > 6) return; 
	if (node == NULL) return;
	node->runCode();
	testGraph(node->getNext());
}

void Graph::printNodes(INode* node) {
	if(node == NULL) return;	
	printNodes(node->printAndSkip());
	
}
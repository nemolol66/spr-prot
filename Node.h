#include <cstring>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Node {
public: 
	Node();
	virtual ~Node();
	Node* getNext();
	int getValue();
	void setNext(Node* nextNode);
	void setValue(int val);

private: 
	Node* next;
	int value;
}




#pragma once
#include "VertexRoute.h"

class NodeRoute {
private:

	struct Node {


		int nodePosition;
		int x;
		int y;
		string color;
		Node* nextNode;

		Node(int pNodePosition, int pX, int pY, string pColor) :
		nodePosition(pNodePosition), x(pX), y(pY), color(pColor), nextNode(nullptr) {}
	};

	Node* head;
	bool isHiddenRoute;

public:
	NodeRoute();
	~NodeRoute();
	
	void addCoords(int, int, string);
	void setHiddenRoute(bool);
	int getX(int);
	int getY(int);
	string getColor(int);
	void printAll(); //temp
};

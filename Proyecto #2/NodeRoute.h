#pragma once
#include <iostream>
#include <stdio.h>

using namespace std;

class NodeRoute {
private:

	struct Node {

		int nodePosition;
		int x;
		int y;
		int color[3];
		Node* nextNode;

		Node(int pNodePosition, int pX, int pY, int pColor[]) :
		nodePosition(pNodePosition), x(pX), y(pY), nextNode(nullptr) 
		{
			for (int i = 0; i < 3; i++) {
				color[i] = pColor[i];
			}
		}
	};

	Node* head;
	bool isHiddenRoute;

public:
	NodeRoute();
	~NodeRoute();
	
	void addCoords(int, int, int[]);
	void clean();
	void setHiddenRoute(bool);
	bool getHiddenRoute();
	int getX(int);
	int getY(int);
	int getColor(int, int);
	void printAll(); //temp
	int getRouteSize();
};

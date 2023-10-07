#pragma once
#include <iostream>

using namespace std;

class VertexRoute {
protected:
	int x;
	int y;

public:
	VertexRoute();
	VertexRoute(int, int);
	~VertexRoute();

	void setX(int);
	void setY(int);
	int getX();
	int getY();

};
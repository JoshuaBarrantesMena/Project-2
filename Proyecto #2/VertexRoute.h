#pragma once
#include <iostream>
#include <stdio.h>

using namespace std;

class VertexRoute { //modificable
protected:
	int x;
	int y;
	string color;

public:
	VertexRoute();
	VertexRoute(int, int, string);
	~VertexRoute();

	void setX(int);
	void setY(int);
	int getX();
	int getY();
	string getColor();
	void setColor(string);

	void print(); //temp

};
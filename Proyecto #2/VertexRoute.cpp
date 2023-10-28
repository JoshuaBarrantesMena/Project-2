#include "VertexRoute.h"

VertexRoute::VertexRoute(){

	x = 0;
	y = 0;
	color = " ";
}

VertexRoute::VertexRoute(int pX, int pY, string pColor) {

	x = pX;
	y = pY;
	color = pColor;
}

VertexRoute::~VertexRoute() {

}

void VertexRoute::setX(int pNewX) {

	x = pNewX;
}

void VertexRoute::setY(int pNewY) {

	y = pNewY;
}

int VertexRoute::getX() {

	return x;
}

int VertexRoute::getY() {

	return y;
}

void VertexRoute::setColor(string pColor) {

	color = pColor;
}

string VertexRoute::getColor() {

	return color;
}

void VertexRoute::print() {

	cout << "X: " << x << "     Y: " << y << "     color: " << color << "\n\n";

}
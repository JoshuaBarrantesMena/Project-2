#include "VertexRoute.h"

VertexRoute::VertexRoute(){

	x = 0;
	y = 0;
}

VertexRoute::VertexRoute(int pX, int pY) {

	x = pX;
	y = pY;
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
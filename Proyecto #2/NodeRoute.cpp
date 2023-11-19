#include "NodeRoute.h"

NodeRoute::NodeRoute() {

	head = nullptr;
	isHiddenRoute = false;
}

NodeRoute::~NodeRoute() {

}

void NodeRoute::addCoords(int pX, int pY, int pColor[]) {

	Node* newNode = new Node(0, pX, pY, pColor);

	if (!head) {
		head = newNode;
	}
	else {
		newNode->nodePosition++;
		Node* actual = head;

		while (actual->nextNode != nullptr) {
			newNode->nodePosition++;
			actual = actual->nextNode;
		}
		actual->nextNode = newNode;
	}
}

void NodeRoute::setHiddenRoute(bool pIsHiddenRoute) {
	isHiddenRoute = pIsHiddenRoute;
}

void NodeRoute::setColor(int pCoordPos, int pNewColor[]) {

	Node* actual = head;
	while (actual->nodePosition != pCoordPos) {
		actual = actual->nextNode;
	}
	actual->color[0] = pNewColor[0];
	actual->color[1] = pNewColor[1];
	actual->color[2] = pNewColor[2];
}

void NodeRoute::clean() {

	Node* actual;
	while (head) {

		actual = head;
		head = head->nextNode;
		delete actual;
	}
	head = nullptr;
}



int NodeRoute::getX(int pNodePos) {

	Node* actual = head;
	while (actual->nodePosition != pNodePos) {
		actual = actual->nextNode;
	}
	return actual-> x;
}

int NodeRoute::getY(int pNodePos) {

	Node* actual = head;
	while (actual->nodePosition != pNodePos) {
		actual = actual->nextNode;
	}
	return actual->y;
}

int NodeRoute::getColor(int pNodePos, int colorPos) {

	Node* actual = head;
	while (actual->nodePosition != pNodePos) {
		actual = actual->nextNode;
	}
	return actual-> color[colorPos];
}

int NodeRoute::getRouteSize() {

	if (!head) {
		return -1;
	}
	Node* actual = head;
	while (actual->nextNode) {
		actual = actual->nextNode;
	}
	return actual->nodePosition;
}

bool NodeRoute::getIsHiddenRoute() {
	return isHiddenRoute;
}
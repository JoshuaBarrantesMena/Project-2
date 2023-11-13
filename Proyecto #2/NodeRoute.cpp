#include "NodeRoute.h"

NodeRoute::NodeRoute() {

	head = nullptr;
	isHiddenRoute = false;
}

NodeRoute::~NodeRoute() {

	/*Node* temp;

	while (head) {
		try {
			temp = head;
			head = head->nextNode;
			delete temp;
		}catch(int error){}
	}*/
}

void NodeRoute::setHiddenRoute(bool pIsHiddenRoute) {

	isHiddenRoute = pIsHiddenRoute;

}

bool NodeRoute::getHiddenRoute() {

	return isHiddenRoute;

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

void NodeRoute::clean() {

	Node* actual;

	while (head) {

		actual = head;
		head = head->nextNode;
		delete actual;
	}
	head = nullptr;
}

void NodeRoute::printAll() {

	Node* actual = head;
	if (isHiddenRoute) {
		//print head
	}
	else {
		while (actual) {
			cout << "Vector de ruta: " << actual->nodePosition + 1 << "\n";
			cout << "X: " << actual->x << "\n";
			cout << "Y: " << actual->y << "\n";

			cout << "R: " << actual->color[0] << "  ";
			cout << "G: " << actual->color[1] << "  ";
			cout << "B: " << actual->color[2] << "  ";
			cout << "\n\n";
			actual = actual->nextNode;
		}
		if (!head) {
			return;
			cout << "eliminado\n\n";
		}
	}
	cout << "\n\n";
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
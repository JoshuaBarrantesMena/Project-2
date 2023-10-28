#include "NodeRoute.h"

NodeRoute::NodeRoute() {

	head = nullptr;
	isHiddenRoute = false;
}

NodeRoute::~NodeRoute() {

	Node* temp;

	while (head) {
		try {
			temp = head->nextNode;
			delete head;
			head = temp;
		}catch(int error){}
	}
}

void NodeRoute::setHiddenRoute(bool pIsHiddenRoute) {

	isHiddenRoute = pIsHiddenRoute;

}

void NodeRoute::addCoords(int pX, int pY, string pColor) {

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

void NodeRoute::printAll() {

	Node* actual = head;

	while (actual) {
		cout << "Vector de ruta: " << actual->nodePosition +1 << "\n";
		cout << "X: " << actual-> x << "\n";
		cout << "Y: " << actual-> y << "\n";
		cout << "Color: " << actual-> color << "\n\n";
		actual = actual->nextNode;
	}
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

string NodeRoute::getColor(int pNodePos) {

	Node* actual = head;
	while (actual->nodePosition != pNodePos) {
		actual = actual->nextNode;
	}
	return actual-> color;
}
#include "NodeRouteList.h"

NodeRouteList::NodeRouteList() {

	lHead = nullptr;
}

NodeRouteList::~NodeRouteList() {

	while (lHead) {
		try {
			NodeList* temp = lHead;
			lHead = lHead->next;
			delete temp;
		}catch(int error){}
	}
}

void NodeRouteList::addRoute(NodeRoute &pRouteNode) {

	NodeList* newNodeRoute = new NodeList(pRouteNode, 0);
	if (!lHead) {
		lHead = newNodeRoute;
	}
	else {
		newNodeRoute->nodePosition++;
		NodeList* actual = lHead;
		while (actual->next) {
			newNodeRoute->nodePosition++;
			actual = actual->next;
		}
		actual->next = newNodeRoute;
	}
}

void NodeRouteList::replaceRoute(NodeRoute pRouteNode, int pRoutePos) {

	NodeList* newRouteNode = new NodeList(pRouteNode, pRoutePos);
	NodeList* actual = lHead;
	NodeList* nextActual = actual->next;
	if (actual->next) {
		while (nextActual->nodePosition != pRoutePos) {
			actual = nextActual;
			nextActual = nextActual->next;
		}
	}
	newRouteNode->next = nextActual->next;
	actual->next = newRouteNode;
	nextActual->next = nullptr;

	delete nextActual;
}

NodeRoute NodeRouteList::getRoute(int pRoutePos) {

	NodeList* actual = lHead;
	while (actual->nodePosition != pRoutePos) {
		actual = actual->next;
	}
	return actual->routeInfo;

}

void NodeRouteList::printAll() {

	NodeList* actual = lHead;

	while (actual) {
		cout << "Ruta: " << actual->nodePosition +1 << "\n";
		actual->routeInfo.printAll();
		actual = actual->next;
	}

}
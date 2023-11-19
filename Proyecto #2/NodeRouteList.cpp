#include "NodeRouteList.h"

NodeRouteList::NodeRouteList() {

	lHead = nullptr;
}

NodeRouteList::~NodeRouteList() {

	NodeList* temp;
	while (lHead) {
		try {
			temp = lHead;
			lHead = lHead->next;
			delete temp;
		}catch(int error){}
	}
} 

void NodeRouteList::addRoute(NodeRoute &pRouteNode) {

	NodeRoute auxRoute;
	int x, y;
	int colors[3];

	auxRoute.setHiddenRoute(pRouteNode.getIsHiddenRoute());

	for (int iter = 0; iter <= pRouteNode.getRouteSize(); iter++) {

		x = pRouteNode.getX(iter);
		y = pRouteNode.getY(iter);
		colors[0] = pRouteNode.getColor(iter, 0);
		colors[1] = pRouteNode.getColor(iter, 1);
		colors[2] = pRouteNode.getColor(iter, 2);

		auxRoute.addCoords(x, y, colors);
	}

	NodeList* newNodeRoute = new NodeList(auxRoute, 0);
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

void NodeRouteList::setRouteColor(int pRoutePos, int pCoordPos, int pNewColor[]) {

	NodeList* actual = lHead;
	while (actual->nodePosition != pRoutePos) {
		actual = actual->next;
	}
	actual->routeInfo.setColor(pCoordPos, pNewColor);
}

void NodeRouteList::setIsHiddenRoute(int pRoutePos, bool pIsHiddenRoute){

	NodeList* actual = lHead;
	while (actual->nodePosition != pRoutePos) {
		actual = actual->next;
	}
	actual->routeInfo.setHiddenRoute(pIsHiddenRoute);
}

void NodeRouteList::clean() {

	NodeList* actual;
	while (lHead) {

		actual = lHead;
		lHead = lHead->next;
		delete actual;
	}
	lHead = nullptr;
}



int NodeRouteList::getListSize() {

	if (!lHead) {
		return -1;
	}
	NodeList* actual = lHead;
	while (actual->next) {
		actual = actual->next;
	}
	return actual->nodePosition;
}

NodeRoute& NodeRouteList::getRoute(int pRoutePos) {

	NodeList* actual = lHead;
	while (actual->nodePosition != pRoutePos) {
		actual = actual->next;
	}
	return actual->routeInfo;
}
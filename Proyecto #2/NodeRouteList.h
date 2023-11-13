#pragma once
#include "NodeRoute.h"

class NodeRouteList {
private:

	struct NodeList {

		NodeRoute routeInfo;
		int nodePosition;
		NodeList* next;

		NodeList(NodeRoute& pRouteInfo, int pNodePosition): routeInfo(pRouteInfo),
			nodePosition(pNodePosition), next(nullptr) {}
	};

	NodeList* lHead;

public:
	NodeRouteList();
	~NodeRouteList();

	void addRoute(NodeRoute&);
	void replaceRoute(NodeRoute, int);
	void clean();
	NodeRoute& getRoute(int);
	void printAll();
	int getListSize(); //conseguir cantidad de rutas
};

#pragma once
#include "VertexRoute.h"

class MapRoute : public VertexRoute {
private:
	string color;
	bool isHidden;

public:
	MapRoute();
	MapRoute(string, bool);
	MapRoute(string, bool,int , int);

	void setColor(string);
	void setHidden(bool);
	string getColor();
	bool getHidden();
};

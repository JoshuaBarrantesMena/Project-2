#include "MapRoute.h"

MapRoute::MapRoute() {


}
MapRoute::MapRoute(string pColor, bool pIsHidden) {

	color = pColor;
	isHidden = pIsHidden;
	x = 0;
	y = 0;
}
MapRoute::MapRoute(string pColor, bool pIsHidden, int pX, int pY) {

	color = pColor;
	isHidden = pIsHidden;
	x = pX;
	y = pY;
}

void MapRoute::setColor(string pColor) {

	color = pColor;
}

void MapRoute::setHidden(bool pIsHidden) {

	isHidden = pIsHidden;
}

string MapRoute::getColor() {

	return color;
}

bool MapRoute::getHidden() {

	return isHidden;
}
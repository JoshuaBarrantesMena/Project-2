#pragma once
#include "NodeRouteList.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <cstdio>

using namespace sf;

void openMap();

void refreshPrincipalInterface();
void refreshCreateInterface();
void refreshEditInterface();
void refreshColorInterface();
void refreshAllRoutes();
void refreshRoute(NodeRoute&);
void refreshSquareSelectedRoute();
void drawLine(Vector2f, Vector2f, int[]);

void detectClickInButton();
void detectClickInCreateRoute();
void detectClickInEditRoute();
void detectClickInColorInterface();
void createRoute();
void detectRoutes();

void saveNewRoute(NodeRoute);
void saveAllRoutes();
void chargeAllRoutes();
void deleteRouteFile(int);

bool isClickingButton(int, int, int, int);
bool mousePositionDetect(Vector2f, Vector2f);
bool isPressingInButton();
bool isPressingInColorInterface();

void loopRefresh();
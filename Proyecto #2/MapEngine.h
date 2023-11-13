#pragma once
#include "NodeRouteList.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <cstdio>

using namespace sf;

void openMap();
void refreshInterface();
void refreshEditInterface();
void refreshCreateInterface();
void refreshColorInterface();

void createRoute();
void refreshAllRoutes();
void refreshRoute(NodeRoute&);
void drawLine(int, int, int, int, int[]);

bool mouseDetect(Vector2f, Vector2f);
bool isClickingButton(int, int, int, int);
bool isPressingInterface();
bool isPressingButton();
bool isPressingColorInterface();

void detectButton();
void detectEditRute();
void detectColorInterface();
void detectRoutes();

void saveNewRoute(NodeRoute);
void saveAllRoutes();
void chargeRoutes();
void deleteRouteFile(int);

void loopRefresh();
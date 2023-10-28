#pragma once
#include "NodeRouteList.h"
#include <SFML/Graphics.hpp>

using namespace sf;

void openMap();
void refreshInterface();
void refreshEditInterface();
void refreshColorInterface();
bool mouseDetect(Vector2f, Vector2f);
bool isClickingButton(int, int, int, int);
void detectButton();
void detectEditRute();
void detectColorInterface();
void loopRefresh();
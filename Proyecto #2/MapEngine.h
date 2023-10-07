#pragma once
#include "MapRoute.h"
#include <SFML/Graphics.hpp>

using namespace sf;

void openMap();
void refreshInterface();
bool mouseDetect(Vector2f, Vector2f);
bool isClickingButton(int, int);
void loopRefresh();
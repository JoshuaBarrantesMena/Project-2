#include "MapEngine.h"

RenderWindow mapWindow(VideoMode(1600, 900), "Mapa de Costa rica");
Texture mapBackgroundFile, buttonFile;
Sprite mapBackground, button;
Font textFont;
Text buttonText;
Event mapEvent;
Vector2i mousePosition;

void openMap() {

	mapWindow.setFramerateLimit(24);

	mapBackgroundFile.loadFromFile("Textures/IMAGE.jpg");
	mapBackground.setTexture(mapBackgroundFile);
	buttonFile.loadFromFile("Textures/Button.png");
	button.setTexture(buttonFile);

	textFont.loadFromFile("Fonts/Cabin-SemiBold.ttf");
	buttonText.setColor(Color(128, 192, 255, 255));
	buttonText.setFont(textFont);
	buttonText.setCharacterSize(35);

	while (mapWindow.isOpen()) {

		refreshInterface();

		loopRefresh();
	}
}

void refreshInterface() {

	int iter, buttonXPosition = 1300;
	int buttonYPositions[4] = { 40, 160, 280, 400 };
	int textPositions[2][4] = {{ 1332, 1346, 1325, 1335 }, {64, 185, 305, 425}};
	string buttonNames[4] = { "Agregar Ruta", "Editar Ruta", "Guardar Rutas", "Cargar Rutas" };

	mapWindow.draw(mapBackground);

	for (iter = 0; iter < 4; iter++) {
		button.setPosition(buttonXPosition, buttonYPositions[iter]);
		mapWindow.draw(button);
		buttonText.setString(buttonNames[iter]);
		buttonText.setPosition(textPositions[0][iter], textPositions[1][iter]);
		mapWindow.draw(buttonText);
	}

	mapWindow.display();
}

bool mouseDetect(Vector2f pTopPosition, Vector2f pBottomPosition) {

	mousePosition = Mouse::getPosition(mapWindow);

	bool isInTop = false;
	bool isInBottom = false;

	if ((mousePosition.x > pTopPosition.x) && (mousePosition.x < pTopPosition.y)) {
		isInTop = true;
	}
	else {
		isInTop = false;
	}

	if ((mousePosition.y > pBottomPosition.x) && (mousePosition.y < pBottomPosition.y)) {
		isInBottom = true;
	}
	else {
		isInBottom = false;
	}

	if (isInTop && isInBottom) {
		return true;
	}
	else {
		return false;
	}
}

bool isClickingButton(int pXPosition, int pYPosition) {

	int minX = pXPosition;
	int maxX = pXPosition + (400 * 0.2);
	int minY = pYPosition;
	int maxY = minY + (600 * 0.2);

	Vector2f top(minX, maxX);
	Vector2f bottom(minY, maxY);

	bool isButtonPressed = false;

	if (Mouse::isButtonPressed(Mouse::Left) && (mouseDetect(top, bottom))) {
		while (isButtonPressed == false) {
			if (Mouse::isButtonPressed(Mouse::Left) != true) {
				isButtonPressed = true;
			}
			loopRefresh();
		}
		return true;
	}
	return false;
}

void loopRefresh() {

	while (mapWindow.pollEvent(mapEvent)) {
		if (mapEvent.type == Event::Closed) {
			mapWindow.close();
		}
	}
}
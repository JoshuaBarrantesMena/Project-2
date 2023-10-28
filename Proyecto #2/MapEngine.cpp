#include "MapEngine.h"

RenderWindow mapWindow(VideoMode(1600, 900), "Mapa de Costa rica");
Texture mapBackgroundFile, buttonFile, colorSelecterFile, colorButtonFile;
Sprite mapBackground, button, colorSelecter, colorButton;
Font textFont;
Text buttonText, colorSelecterText;
Event mapEvent;
Vector2i mousePosition;

const int buttonXPosition = 1300;
const int buttonYPositions[] = { 40, 160, 280, 400 };
const int colorButtonPos[2][3] = { {110, 210, 310}, {470, 550, 630} };
const int colorCodes[3][9] = 
	{ 
	{96, 0, 0, 64, 128, 0, 255, 128, 64},
	{0, 96, 0, 0, 64, 128, 64, 255, 128},
	{0, 0, 96, 128, 0, 64, 128, 64, 255}, 
	};
int globalColor[3] = { 255, 255, 255,};
int interfaceNumber;

void openMap() {

	mapWindow.setFramerateLimit(24);

	mapBackgroundFile.loadFromFile("Textures/IMAGE.jpg");
	mapBackground.setTexture(mapBackgroundFile);
	buttonFile.loadFromFile("Textures/Button.png");
	button.setTexture(buttonFile);

	colorButtonFile.loadFromFile("Textures/ColorButton.png");
	colorButton.setTexture(colorButtonFile);
	colorButton.setColor(Color::White);

	textFont.loadFromFile("Fonts/Cabin-SemiBold.ttf");
	buttonText.setColor(Color(128, 192, 255, 255));
	buttonText.setFont(textFont);
	buttonText.setCharacterSize(35);

	colorSelecterFile.loadFromFile("Textures/ColorSelecter.png");
	colorSelecter.setTexture(colorSelecterFile);
	colorSelecter.setPosition(50, 390);
	colorSelecter.setScale(1.1, 1.5);
	colorSelecterText.setFont(textFont);
	colorSelecterText.setCharacterSize(35);
	colorSelecterText.setColor(Color(128,192,255,255));

	interfaceNumber = 0;

	while (mapWindow.isOpen()) {

		switch (interfaceNumber) {

		case 1:

			refreshEditInterface();
			break;
		case 2:

			refreshEditInterface();
			break;

		case 3:
			interfaceNumber = 0;
			break;

		case 4:
			interfaceNumber = 0;
			break;

		default:

			refreshInterface();
			break;
		}

		loopRefresh();
	}
}

void refreshInterface() {

	int iter;
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
	detectButton();
}
void refreshEditInterface(){

	int iter;
	int textPositions[2][3] = { { 1328, 1330, 1333 }, {64, 185, 305} };
	string buttonNames[3] = { "Finalizar Ruta", "Eliminar Ruta", "Ocultar Ruta" };

	mapWindow.draw(mapBackground);

	for (iter = 0; iter < 3; iter++) {
		button.setPosition(buttonXPosition, buttonYPositions[iter]);
		mapWindow.draw(button);
		buttonText.setString(buttonNames[iter]);
		buttonText.setPosition(textPositions[0][iter], textPositions[1][iter]);
		mapWindow.draw(buttonText);
	}

	refreshColorInterface();
	detectEditRute();
	detectColorInterface();
}

void refreshColorInterface(){

	int auxIterX, auxIterY, colorIter = 0;


	mapWindow.draw(colorSelecter);
	colorSelecterText.setString("Elegir color de la ruta");
	colorSelecterText.setPosition(90, 410);
	mapWindow.draw(colorSelecterText);

	for (auxIterY = 0; auxIterY < 3; auxIterY++) {
		for (auxIterX = 0; auxIterX < 3; auxIterX++) {
		colorButton.setPosition(colorButtonPos[0][auxIterX], colorButtonPos[1][auxIterY]);

		colorButton.setColor(Color(colorCodes[0][colorIter], colorCodes[1][colorIter],
					colorCodes[2][colorIter], 255));
		mapWindow.draw(colorButton);
		colorIter++;
		}
	}
	colorSelecterText.setPosition(90, 750);
	colorSelecterText.setString("Color elegido:");
	mapWindow.draw(colorSelecterText);

	colorButton.setColor(Color(globalColor[0], globalColor[1], globalColor[2], 255));
	colorButton.setPosition(310, 740);
	mapWindow.draw(colorButton);
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

bool isClickingButton(int pXPosition, int pXSizePosition, int pYPosition, int pYSizePosition) {

	int minX = pXPosition;
	int maxX = pXPosition + (pXSizePosition);
	int minY = pYPosition;
	int maxY = minY + (pYSizePosition);

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

void detectButton() {

	int buttonIter;

	for (buttonIter = 0; buttonIter < 4; buttonIter++) {
		
		if (isClickingButton(buttonXPosition, 260, buttonYPositions[buttonIter], 100)) {
			cout << "Interface #" << buttonIter + 1 << "\n" << "\n"; //temp
			interfaceNumber = buttonIter + 1;
		}
	}
}

void detectEditRute(){

	int optionIter, option = 0;
	bool isChoosingButton = true;

	for (optionIter = 0; optionIter < 3; optionIter++) {
		if (isClickingButton(buttonXPosition, 260, buttonYPositions[optionIter], 100)) {
			cout << "Edit #" << optionIter + 1 << "\n" << "\n"; //temp
			option = optionIter + 1;
			isChoosingButton = false;
		}
	}

	switch (option) {
	default:
		break;
	case 1:
		interfaceNumber = 0;
		break;
	case 2:
		interfaceNumber = 0;
		break;
	case 3:
		break;
	}
}

void detectColorInterface(){

	int colorIterX, colorIterY, option = 0;
	bool isChoosingButton = true;

	for (colorIterY = 0; colorIterY < 3; colorIterY++) {
		for (colorIterX = 0; colorIterX < 3; colorIterX++) {
			if (isClickingButton(colorButtonPos[0][colorIterX], 70, colorButtonPos[1][colorIterY], 70)) {
				cout << "Color # (" << colorIterX + 1 << ", " << colorIterY + 1 << ")" << "\n" << "\n"; //temp
				
				globalColor[0] = colorCodes[0][option];
				globalColor[1] = colorCodes[1][option];
				globalColor[2] = colorCodes[2][option];
				isChoosingButton = false;
			}
			option++;
		}
	}
}

void loopRefresh() {

	while (mapWindow.pollEvent(mapEvent)) {
		if (mapEvent.type == Event::Closed) {
			mapWindow.close();
		}
	}
}
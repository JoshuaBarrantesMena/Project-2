#include "MapEngine.h"

RenderWindow mapWindow(VideoMode(1600, 900), "Mapa de Costa rica");
Texture mapBackgroundFile, buttonFile, colorSelecterFile, colorButtonFile;
Sprite mapBackground, button, colorSelecter, colorButton;
Font textFont;
Text buttonText, colorSelecterText;
Event mapEvent;
Vector2i mousePosition;

NodeRouteList routesList;
NodeRoute temporalRoute;

ifstream readFile;

const int buttonXPosition = 1300;
const int buttonYPositions[4] = { 40, 160, 280, 400 };
const int colorButtonPos[2][3] = { {110, 210, 310}, {470, 550, 630} };
const int colorCodes[3][9] = 
	{ 
	{96, 0, 0, 64, 128, 0, 255, 128, 64},
	{0, 96, 0, 0, 64, 128, 64, 255, 128},
	{0, 0, 96, 128, 0, 64, 128, 64, 255}, 
	};
int globalColor[3] = { 96, 0, 0};
int interfaceNumber, selectedRoute = -1, selectedCoord = -1;
bool globalHiddenRoute;

void openMap() {

	mapWindow.setFramerateLimit(60);

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
	globalHiddenRoute = false;

	while (mapWindow.isOpen()) {

		switch (interfaceNumber) {

		case 1:
			refreshCreateInterface();
			break;

		case 2:
			if (selectedRoute != -1 && selectedCoord != -1) {
				refreshEditInterface();
			}
			else {
				interfaceNumber = 0;
			}
			break;

		case 3:
			saveAllRoutes();
			interfaceNumber = 0;
			break;

		case 4:
			chargeRoutes();
			routesList.printAll();

			interfaceNumber = 0;
			break;

		default:

			refreshInterface();
			break;
		}
		if(interfaceNumber != 2){
			detectRoutes();
		}

		refreshAllRoutes();
		refreshSelectedRoute();
		mapWindow.display();
		loopRefresh();
	}
	routesList.clean();
	temporalRoute.clean();
}

void refreshInterface() {

	int iter;
	int textPositions[2][4] = {{ 1332, 1346, 1325, 1335 }, {64, 185, 305, 425}};
	string buttonNames[4] = { "Agregar Ruta", "Editar Ruta", "Guardar Rutas", "Cargar Rutas" };

	mapWindow.draw(mapBackground);

	for (iter = 0; iter < 4; iter++) {

		button.setPosition(buttonXPosition, buttonYPositions[iter]);
		if (iter == 1 && selectedRoute == -1) {
			Sprite auxButton = button;
			auxButton.setColor(Color(224, 224, 224, 255));
			mapWindow.draw(auxButton);
		}
		else {
			mapWindow.draw(button);
		}

		buttonText.setString(buttonNames[iter]);
		buttonText.setPosition(textPositions[0][iter], textPositions[1][iter]);
		mapWindow.draw(buttonText);
	}
	detectButton();
}
void refreshEditInterface(){

	int iter;
	int textPositions[2][3] = { { 1328, 1330, 1333 }, {64, 185, 305} };
	int temporalColor[3];
	string buttonNames[3] = { "Finalizar Ruta", "Eliminar Ruta", "Ocultar Ruta" };

	globalColor[0] = routesList.getRoute(selectedRoute).getColor(selectedCoord, 0);
	globalColor[1] = routesList.getRoute(selectedRoute).getColor(selectedCoord, 1);
	globalColor[2] = routesList.getRoute(selectedRoute).getColor(selectedCoord, 2);

	mapWindow.draw(mapBackground);

	for (iter = 0; iter < 3; iter++) {
		button.setPosition(buttonXPosition, buttonYPositions[iter]);
		mapWindow.draw(button);
		buttonText.setString(buttonNames[iter]);
		buttonText.setPosition(textPositions[0][iter], textPositions[1][iter]);
		mapWindow.draw(buttonText);
	}

	refreshColorInterface();
	detectColorInterface();
	routesList.setRouteColor(selectedRoute, selectedCoord, globalColor);

	detectEditRoute();

}

void refreshCreateInterface() {

	int iter;
	int textPositions[2][3] = { { 1328, 1330, 1333 }, {64, 185, 305} };
	string buttonNames[2] = { "Finalizar Ruta", "Eliminar Ruta"};

	globalColor[0] = 96;
	globalColor[1] = 0;
	globalColor[2] = 0;

	mapWindow.draw(mapBackground);

	for (iter = 0; iter < 2; iter++) {
		button.setPosition(buttonXPosition, buttonYPositions[iter]);
		mapWindow.draw(button);
		buttonText.setString(buttonNames[iter]);
		buttonText.setPosition(textPositions[0][iter], textPositions[1][iter]);
		mapWindow.draw(buttonText);
	}

	refreshColorInterface();
	detectCreateRoute();
	detectColorInterface();
	createRoute();
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
}





void createRoute() {

	bool isButtonPressed = false;

	mousePosition = Mouse::getPosition(mapWindow);

	refreshRoute(temporalRoute);

	if ((mousePosition.x < 0 || mousePosition.x > 1600) || (mousePosition.y < 0 || 
		mousePosition.y > 900)) {

		return;
	}

	if (Mouse::isButtonPressed(Mouse::Left ) && isPressingInterface() != true) {
		while (isButtonPressed == false) {
			if (Mouse::isButtonPressed(Mouse::Left) != true) {
				isButtonPressed = true;
				temporalRoute.addCoords(mousePosition.x, mousePosition.y, globalColor);
				temporalRoute.setHiddenRoute(globalHiddenRoute);
				temporalRoute.printAll();
			}
			loopRefresh();
		}
	}
}



void refreshAllRoutes() {

	int listIter;
	int listSize = routesList.getListSize();

	for (listIter = 0; listIter < listSize + 1; listIter++) {

		refreshRoute(routesList.getRoute(listIter));
		
	}
}

void refreshRoute(NodeRoute& pRoute) {

	int routeSize;
	int routeIter, colorIter;
	int x, y, xAux = -1, yAux = -1, routeColor[3];
	CircleShape circle(10);
	

	routeSize = pRoute.getRouteSize();

	if (pRoute.getHiddenRoute()) {

		x = pRoute.getX(0);
		y = pRoute.getY(0);
		for (colorIter = 0; colorIter < 3; colorIter++) {
			routeColor[colorIter] = pRoute.getColor(0, colorIter);
		}

		circle.setPosition(x - 10, y - 10);
		circle.setFillColor(Color(routeColor[0], routeColor[1], routeColor[2], 255));
		mapWindow.draw(circle);
		circle.setRadius(5);

		for (colorIter; colorIter < 3; colorIter++) {
			if ((routeColor[colorIter] - 32) >= 0) {
				routeColor[colorIter] -= 32;
			}
		}
		circle.setFillColor(Color(routeColor[0], routeColor[1], routeColor[2], 255));
		circle.setPosition(x - 5, y - 5);
		mapWindow.draw(circle);
		circle.setRadius(10);

	}
	else {
		for (routeIter = 0; routeIter < routeSize + 1; routeIter++) {

			x = pRoute.getX(routeIter);
			y = pRoute.getY(routeIter);
			for (colorIter = 0; colorIter < 3; colorIter++) {
				routeColor[colorIter] = pRoute.getColor(routeIter, colorIter);
			}

			circle.setPosition(x - 10, y - 10);
			circle.setFillColor(Color(routeColor[0], routeColor[1], routeColor[2], 255));
			mapWindow.draw(circle);

			if (xAux >= 0 && yAux >= 0) {
				drawLine(x, y, xAux, yAux, routeColor);
			}
			xAux = x;
			yAux = y;
		}
	}

}

void refreshSelectedRoute() {

	if (selectedRoute != -1) {

		int routeSize = routesList.getRoute(selectedRoute).getRouteSize(), squareSizeIter, thicknessIter;

		int minX, minY, maxX, maxY, coordBonus = 12;

		minX = routesList.getRoute(selectedRoute).getX(0);
		minY = routesList.getRoute(selectedRoute).getY(0);
		maxX = routesList.getRoute(selectedRoute).getX(0);
		maxY = routesList.getRoute(selectedRoute).getY(0);

		for (squareSizeIter = 0; squareSizeIter <= routeSize; squareSizeIter++) {
			if (routesList.getRoute(selectedRoute).getX(squareSizeIter) < minX) {
				minX = routesList.getRoute(selectedRoute).getX(squareSizeIter);
			}
			if (routesList.getRoute(selectedRoute).getY(squareSizeIter) < minY) {
				minY = routesList.getRoute(selectedRoute).getY(squareSizeIter);
			}
			if (routesList.getRoute(selectedRoute).getX(squareSizeIter) > maxX) {
				maxX = routesList.getRoute(selectedRoute).getX(squareSizeIter);
			}
			if (routesList.getRoute(selectedRoute).getY(squareSizeIter) > maxY) {
				maxY = routesList.getRoute(selectedRoute).getY(squareSizeIter);
			}
		}

		minX -= coordBonus;
		minY -= coordBonus;
		maxX += coordBonus;
		maxY += coordBonus;

		const int squareThickness = 3;
		int squareColor[3] = { 255, 0, 127 };

		for (thicknessIter = 0; thicknessIter < squareThickness; thicknessIter++) {

			drawLine(minX, minY, maxX, minY, squareColor);
			drawLine(maxX, minY, maxX, maxY, squareColor);
			drawLine(maxX, maxY, minX, maxY, squareColor);
			drawLine(minX, maxY, minX, minY, squareColor);

			minX--;
			minY--;
			maxX++;
			maxY++;
		}
	}
}

void drawLine(int pX1, int pY1, int pX2, int pY2, int color[]) {

	Color pixel(color[0], color[1], color[2], 255);
	Image line;
	line.create(1600, 900, Color(0, 0, 0, 0));
	int xCoord, yCoord, pixelPrinter, pixelIter;
	float x, y, xIncreaser, yIncreaser;

	xCoord = pX1 - pX2;
	yCoord = pY1 - pY2;

	pixelPrinter = 0;

	if (abs(xCoord) > abs(yCoord)) {
		pixelPrinter = abs(xCoord);
	}
	else {
		pixelPrinter = abs(yCoord);
	}

	xIncreaser = xCoord / (float)pixelPrinter;
	yIncreaser = yCoord / (float)pixelPrinter;

	x = pX2;
	y = pY2;

	for (pixelIter = 0; pixelIter < pixelPrinter; pixelIter++) {
		line.setPixel(round(x), round(y), pixel);
		x += xIncreaser;
		y += yIncreaser;
	}

	Texture lineTexture;
	lineTexture.loadFromImage(line);
	Sprite newLine(lineTexture);
	mapWindow.draw(newLine);
}





bool mouseDetect(Vector2f pTopPosition, Vector2f pBottomPosition) {

	mousePosition = Mouse::getPosition(mapWindow);

	if ((mousePosition.x < 0 || mousePosition.x > 1600) || (mousePosition.y < 0 ||
		mousePosition.y > 900)) {

		return false;
	}

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

bool isPressingInterface() {

	if (isPressingButton() || isPressingColorInterface()) {
		return true;
	}
	return false;
}

bool isPressingButton() {

	int minX = buttonXPosition;
	int maxX = minX + 260;

	bool clickDetected = false;

	for (int buttonIter = 0; buttonIter < 4; buttonIter++) {

		int minY = buttonYPositions[buttonIter];
		int maxY = minY + 100;

		if (mouseDetect(Vector2f(minX, maxX), Vector2f(minY, maxY))) {
			return true;
		}
		if (clickDetected) {
			continue;
		}
	}
	return clickDetected;
}

bool isPressingColorInterface() {

	int minX = 50;
	int maxX = minX + (360 * 1.1);
	int minY = 390;
	int maxY = minY + (300 * 1.5);

	if (mouseDetect(Vector2f(minX, maxX), Vector2f(minY, maxY))) {
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

void detectEditRoute(){ //pendiente

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
		selectedRoute = -1;
		selectedCoord = -1;
		interfaceNumber = 0;
		break;
	case 2:
		deleteRouteFile(selectedRoute);
		chargeRoutes();
		selectedRoute = -1;
		selectedCoord = -1;
		interfaceNumber = 0;
		break;
	case 3:
		if (routesList.getRoute(selectedRoute).getHiddenRoute()) {
			routesList.setIsHiddenRoute(selectedRoute, false);
		}
		else {
			routesList.setIsHiddenRoute(selectedRoute, true);
		}
		break;
	}
}

void detectCreateRoute() {

	int optionIter, option = 0;
	bool isChoosingButton = true;

	for (optionIter = 0; optionIter < 2; optionIter++) {
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
		saveNewRoute(temporalRoute);
		selectedRoute = -1;
		selectedCoord = -1;
		interfaceNumber = 0;
		globalHiddenRoute = false;
		break;
	case 2:
		temporalRoute.clean();
		selectedRoute = -1;
		selectedCoord = -1;
		interfaceNumber = 0;
		globalHiddenRoute = false;
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

void detectRoutes() {

	int x, y, xSize = 20, ySize = 20, listIter, routeIter;
	int routesListSize = routesList.getListSize(), routeSize;

	for (listIter = 0; listIter <= routesListSize; listIter++) {

		routeSize = routesList.getRoute(listIter).getRouteSize();

		for (routeIter = 0; routeIter <= routeSize; routeIter++) {

			x = routesList.getRoute(listIter).getX(routeIter) - 10;
			y = routesList.getRoute(listIter).getY(routeIter) - 10;

			if (isClickingButton(x, xSize, y, ySize)) {
				selectedRoute = listIter;
				selectedCoord = routeIter;

				cout << "\n\nRuta seleccionada: " << listIter << "\n"; //temp
				cout << "coordenada seleccionada: " << routeIter << "\n\n\n"; //temp
			}
		}
	}
}





void saveNewRoute(NodeRoute pRoute) {
	
	if (pRoute.getRouteSize() < 1) {
		temporalRoute.clean();
		return;
	}

	string url = "Routes/r", type = ".txt", name;
	int routeIter = 0;

	name = url + to_string(routeIter) + type;

	readFile.open(name);

	while (readFile.is_open() != false) {

		readFile.close();

		routeIter++;
		name = url + to_string(routeIter) + type;
		readFile.open(name);
		loopRefresh();
	}

	ofstream createFile(name);

	int size = pRoute.getRouteSize();
	int verifyInt = 0, secondIter;
	string intNum;

	createFile << pRoute.getHiddenRoute() << endl;

	for (routeIter = 0; routeIter <= size; routeIter++) {

		createFile << pRoute.getX(routeIter) << endl;
		createFile << pRoute.getY(routeIter) << endl;

		for (secondIter = 0; secondIter < 3; secondIter++) {

			verifyInt = pRoute.getColor(routeIter, secondIter);
			if (verifyInt < 100 && verifyInt >= 10) {

				intNum = "0" + to_string(verifyInt);

			} else if (verifyInt < 10) {

				intNum = "00" + to_string(verifyInt);
			}
			else {
				intNum = to_string(verifyInt);
			}
			createFile << intNum << " ";
		}
		createFile << endl;
	}
	createFile << ";";
	createFile.close();
	routesList.addRoute(temporalRoute);
	temporalRoute.clean();
}

void saveAllRoutes() {

	int routeIter, routeListSize = routesList.getListSize();

	for (routeIter = 0; routeIter <= routeListSize; routeIter++) {

		deleteRouteFile(routeIter);

	}

	for (routeIter = 0; routeIter <= routeListSize; routeIter++) {

		saveNewRoute(routesList.getRoute(routeIter));

	}
}

void chargeRoutes() {

	routesList.clean();

	const int maxRoutes = 99;
	int routeIter = 0;
	string url = "Routes/r", type = ".txt", name;
	string line;

	int x, y;
	int colors[3];

	ifstream file;

	NodeRoute newRoute;
	
	for (routeIter; routeIter < maxRoutes; routeIter++) {

		name = url + to_string(routeIter) + type;

		file.open(name);

		if (!file.is_open()) {
			continue;
		}

		getline(file, line);

		newRoute.setHiddenRoute(atoi(line.c_str()));

		getline(file, line);
		while (line != ";") {

			x = atoi(line.c_str());
			getline(file, line);
			y = atoi(line.c_str());
			getline(file, line);
			for (int iter = 0; iter < 3; iter++) {
				colors[iter] = atoi(line.substr(0, 3).c_str());
				line.erase(0, 4);
			}
			newRoute.addCoords(x, y, colors);
			getline(file, line);
		}
		routesList.addRoute(newRoute);
		newRoute.clean();
		
		file.close();
	}
}

void deleteRouteFile(int pRouteNum) {

	string url = "Routes/r", type = ".txt", name;
	char fullName[16];

	name = url + to_string(pRouteNum) + type;
	strcpy(fullName, name.c_str());

	remove(fullName);

}





void loopRefresh() {

	while (mapWindow.pollEvent(mapEvent)) {
		if (mapEvent.type == Event::Closed) {
			mapWindow.close();
		}
	}
}
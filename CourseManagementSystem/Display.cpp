#include "Display.h"
#include "Graphic.h"

void drawTutorial(int x, int y, int width, int height) {
	char horizontalLine = '-';
	char verticalLine = '|';
	char topLeftCorner = '+';
	char topRightCorner = '+';
	char bottomLeftCorner = '+';
	char bottomRightCorner = '+';

	// Draw the top line of the box
	gotoxy(x, y);
	std::cout << topLeftCorner;
	for (int i = 1; i < width - 1; i++) {
		std::cout << horizontalLine;
	}
	std::cout << topRightCorner;

	// Draw the sides of the box
	for (int i = 1; i < height - 1; i++) {
		gotoxy(x, y + i);
		std::cout << verticalLine;
		gotoxy(x + width - 1, y + i);
		std::cout << verticalLine;
	}

	// Draw the bottom line of the box
	gotoxy(x, y + height - 1);
	std::cout << bottomLeftCorner;
	for (int i = 1; i < width - 1; i++) {
		std::cout << horizontalLine;
	}
	std::cout << bottomRightCorner;
}

void Tutorial() {
	int mid = 15 + 30 / 2;
	gotoxy(mid - 9/2, 2);
	SetColor(7, 1);
	std::cout << "Tutorial";
	SetColor(7, 0);

	gotoxy(mid - 20 / 2, 6);
	std::cout << "Press n - Next Page";

	gotoxy(mid - 24 / 2, 10);
	std::cout << "Press p - Previous Page";

	gotoxy(mid - 20 / 2, 14);
	std::cout << "(number) - Nth Page";

	gotoxy(mid - 22 / 2, 18);
	std::cout << "Press Enter - Go Back";
}
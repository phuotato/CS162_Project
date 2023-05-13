#include "Display.h"
#include "Graphic.h"
#include <string>

int movingBarTutorial(int x, int y, int yp, int limitx, int limity, int steep, std::string* content) {
	int mid = 15 + 30 / 2;
	int xp = x;
	int count = (yp - y) / steep;
	char c = 1;

	//SetColor(4, 0);
	SetColor(4, 7);
	gotoxy(x, yp);
	for (int i = 0; i < limitx - x; i++) std::cout << " ";
	gotox(mid - content[count].length() / 2); std::cout << content[count];
	SetColor(7, 0);
	setcursor(0, 0);


	while (true) {
		if (_kbhit())
		{
			if (c == -32) // c = 224 is the special for keystrokes
			{
				c = _getch();
				if (c == 72) //up
				{
					if (yp != y) {
						//Reset
						gotoxy(x, yp);
						for (int i = 0; i < limitx - x; i++) std::cout << " ";
						gotox(mid - content[count].length() / 2); std::cout << content[count];

						//Calculate new bar
						yp -= steep;
						count--;
						//SetColor(4, 0);
						SetColor(4, 7);

						gotoxy(x, yp);
						for (int i = 0; i < limitx - x; i++) std::cout << " ";
						gotox(mid - content[count].length() / 2); std::cout << content[count];
						SetColor(7, 0);
					}
					else
					{
						//Reset
						gotoxy(x, yp);
						for (int i = 0; i < limitx - x; i++) std::cout << " ";
						gotox(mid - content[count].length() / 2); std::cout << content[count];

						//Calculate new bar
						yp = limity;
						count = (limity - y) / steep;
						//SetColor(4, 0);
						SetColor(4, 7);
						gotoxy(x, yp);
						for (int i = 0; i < limitx - x; i++) std::cout << " ";
						gotox(mid - content[count].length() / 2); std::cout << content[count];
						SetColor(7, 0);
					}
				}
				else if (c == 80) //down
				{
					if (yp != limity) {
						//Reset
						gotoxy(x, yp);
						for (int i = 0; i < limitx - x; i++) std::cout << " ";
						gotox(mid - content[count].length() / 2); std::cout << content[count];

						//Calculate new bar
						yp += steep;
						count++;
						//SetColor(4, 0);
						SetColor(4, 7);
						gotoxy(x, yp);
						for (int i = 0; i < limitx - x; i++) std::cout << " ";
						gotox(mid - content[count].length() / 2); std::cout << content[count];
						SetColor(7, 0);
					}
					else
					{
						//Reset
						gotoxy(x, yp);
						for (int i = 0; i < limitx - x; i++) std::cout << " ";
						gotox(mid - content[count].length() / 2); std::cout << content[count];

						//Calculate new bar
						yp = y;
						count = 0;
						//SetColor(4, 0);
						SetColor(4, 7);
						gotoxy(x, yp);
						for (int i = 0; i < limitx - x; i++) std::cout << " ";
						gotox(mid - content[count].length() / 2); std::cout << content[count];
						SetColor(7, 0);
					}
				}
			}
		}
		else if (c == 13) {
			setcursor(1, 10);

			//Reset
			SetColor(7, 0);
			gotoxy(x, yp);
			for (int i = 0; i < limitx - x; i++) std::cout << " ";
			gotox(mid - content[count].length() / 2); std::cout << content[count];

			return (limity - yp) / steep;
		}
		else c = _getch();
	}

}

int movingBar(int x, int y, int yp, int limitx, int limity, int steep, std::string* content) {
	int xp = x;
	int count = (yp-y)/steep;
	char c = 1;

	//SetColor(4, 0);
	SetColor(4, 7);
	gotoxy(x, yp);
	for (int i = 0; i < limitx - x; i++) std::cout << " ";
	gotox(x + 1); std::cout << content[count];
	SetColor(7, 0);
	setcursor(0, 0);


	while (true) {
		if (_kbhit())
		{
			if (c == -32) // c = 224 is the special for keystrokes
			{
				c = _getch();
				if (c == 72) //up
				{
					//Checking for separate line
					if (yp != y) {
						//Reset
						gotoxy(x, yp);
						for (int i = 0; i < limitx - x; i++) std::cout << " ";
						gotox(x + 1); std::cout << content[count];

						//check if the next one is line
						if (content[count - 1] == "-") {
							count -= 1;
							yp -= steep;
						}

						//Calculate new bar
						yp -= steep;
						count--;
						//SetColor(4, 0);
						SetColor(4, 7);
						gotoxy(x, yp);
						for (int i = 0; i < limitx - x; i++) std::cout << " ";
						gotox(x + 1); std::cout << content[count];
						SetColor(7, 0);
					}
					else
					{
						//Reset
						gotoxy(x, yp);
						for (int i = 0; i < limitx - x; i++) std::cout << " ";
						gotox(x + 1); std::cout << content[count];

						//Calculate new bar
						yp = limity;
						count = (limity - y) / steep;
						//SetColor(4, 0);
						SetColor(4, 7);
						gotoxy(x, yp);
						for (int i = 0; i < limitx - x; i++) std::cout << " ";
						gotox(x + 1); std::cout << content[count];
						SetColor(7, 0);
					}
				}
				else if (c == 80) //down
				{
					if (yp != limity) {
						//Reset
						gotoxy(x, yp);
						for (int i = 0; i < limitx - x; i++) std::cout << " ";
						gotox(x + 1); std::cout << content[count];

						//check if the next one is line
						if (content[count + 1] == "-") {
							count += 1;
							yp += steep;
						}

						//Calculate new bar
						yp += steep;
						count++;
						//SetColor(4, 0);
						SetColor(4, 7);
						gotoxy(x, yp);
						for (int i = 0; i < limitx - x; i++) std::cout << " ";
						gotox(x + 1); std::cout << content[count];
						SetColor(7, 0);
					}
					else
					{
						//Reset
						gotoxy(x, yp);
						for (int i = 0; i < limitx - x; i++) std::cout << " ";
						gotox(x + 1); std::cout << content[count];

						//Calculate new bar
						yp = y;
						count = 0;
						//SetColor(4, 0);
						SetColor(4, 7);
						gotoxy(x, yp);
						for (int i = 0; i < limitx - x; i++) std::cout << " ";
						gotox(x + 1); std::cout << content[count];
						SetColor(7, 0);
					}
				}
			}
			else c = _getch();
		}
		else if (c == 13) {
			setcursor(1, 10);

			//Reset
			SetColor(7, 0);
			gotoxy(x, yp);
			for (int i = 0; i < limitx - x; i++) std::cout << " ";
			gotox(x + 1); std::cout << content[count];

			return (limity - yp) / steep;
		}
		
		else c = _getch();
	}

}

void Tutorial(std::string*& content) {
	content = new std::string[4];
	int mid = 15 + 30 / 2;

	gotoxy(mid - 5, 2);
	SetColor(7, 1);
	std::cout << "Navigation";
	SetColor(7, 0);

	gotoxy(mid - 9/2, 6);
	std::cout << "Next Page";
	content[0] = "Next Page";

	gotoxy(mid - 13/2, 10);
	std::cout << "Previous Page";
	content[1] = "Previous Page";

	gotoxy(mid - 8, 14);
	std::cout << "Change List Length";
	content[2] = "Change List Length";

	gotoxy(mid - 7/2, 18);
	std::cout << "Confirm";
	content[3] = "Confirm";
}


int YNQuestions(int x, int y, int size) {
	drawBox(x, y, size, 6);
	gotoy(y + 2);
	drawLine(size, x);

	std::string* content = new std::string[2];
	content[0] = "Yes.";
	content[1] = "No.";
	gotoxy(x + 2, y + 4); std::cout << "No.";
	int option = movingBar(x + 1, y + 3, y + 3, size-1, y+4, 1, content);
	
	switch (option) {
		case 1:
			return 1;
		case 2:
			return 0;
	}
}

void Description(short range, short APages, short CPages, short Pcur, int Tablex, int Tablewidth) {
	int mid = Tablex + Tablewidth / 2;
	SetColor(7, 1);
	gotox(mid - 12 / 2);
	std::cout << "Pages: " << CPages << "/" << APages;
	SetColor(7, 0);

	gotoxy(Tablex+1, -1);
	if (Pcur % range == 0) std::cout << "Showing " << Pcur - (range-1) << "-" << Pcur;
	else std::cout << "Showing " << Pcur - (Pcur%range) + 1 << "-" << Pcur;



	gotox(Tablex + Tablewidth - 7 - (range/10) - 3);
	std::cout << "List: " << range;
}
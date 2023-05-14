#include "Graphic.h"
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE console_color;

void setcursor(bool visible, DWORD size) // set bool visible = 0 - invisible, bool visible = 1 - visible
{
	if (size == 0)
	{
		size = 20;	// default cursor size Changing to numbers from 1 to 20, decreases cursor width
	}
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);
}

void gotoxy(short a, short b) {
	COORD coordinates{};
	coordinates = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));

	//Format if the number is negative - then that position minus
	if (a < 0) coordinates.X += a;
	else coordinates.X = a;

	if (b < 0) coordinates.Y += b;
	else coordinates.Y = b;
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void gotox(short a) {
	COORD coordinates{};
	coordinates = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));

	//Format if the number is negative - then that position minus
	if (a < 0) coordinates.X += a;
	else coordinates.X = a;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void gotoy(short a) {
	COORD coordinates{};
	coordinates = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));

	//Format if the number is negative - then that position minus
	if (a < 0) coordinates.Y += a;
	else coordinates.Y = a;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void SetColor(int backgound_color, int text_color)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	int color_code = backgound_color * 16 + text_color;
	SetConsoleTextAttribute(hStdout, color_code);
}

void setColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void setBackgroundColor(int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	SetConsoleTextAttribute(hConsole, color);
}

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		// The function failed. Call GetLastError() for details.
		COORD invalid = { 0, 0 };
		return invalid;
	}
}

void drawBox(int x, int y, int width, int height) {
	for (int i = 0; i < height; i++) {
		gotoxy(x, y + i);
		for (int j = 0; j < width; j++) {
			if (i == 0 && j == width - 1) {
				std::cout << char(191); //top right corner
			}
			else if (i == 0 && j == 0) {
				std::cout << char(218);	//top left corner
			}
			else if (i == height - 1 && j == 0) {
				std::cout << char(192); //bottom right corner
			}
			else if (i == height - 1 && j == width - 1) {
				std::cout << char(217); //bottom left corner
			}
			else if (i == 0 || i == height - 1) {
				std::cout << char(196);
			}
			else {
				if (j == width - 1 || j == 0) std::cout << char(179);
				else gotox(x + width - 1);
			}
		}

	}
}

void drawLine(int length, short x) {
	gotox(x);
	std::cout << char(195);
	for (int i = 1; i < length-1; i++) {
		std::cout << char(196);
	}
	std::cout << char(180);
	gotox(x);
}

void drawHeader() {
	int Mid = getMidColumns();
	gotoxy(Mid-49/2, 2); std::cout << " ____  __  ____    _  _   ___  _  _  _  _  ____  " << "\n";
	gotoxy(Mid-49/2, 3); std::cout << "(  __)(  )(_  _)  / )( \\ / __)( \\/ )/ )( \\/ ___) " << "\n";
	gotoxy(Mid-49/2, 4); std::cout << " ) _)  )(   )(  _ ) __ (( (__ / \\/ \\) \\/ (\\___ \\ " << "\n";
	gotoxy(Mid-49/2, 5); std::cout << "(__)  (__) (__)(_)\\_)(_/ \\___)\\_)(_/\\____/(____/ " << "\n";
}

//void loadingPage() {
//	std::cout << "#############################################################" << std::endl;
//	std::cout << "#                    _                                      #" << std::endl;
//	std::cout << "#                  -=\\`\\                                    #" << std::endl;
//	std::cout << "#              |\\ ____\\_\\__                                 #" << std::endl;
//	std::cout << "#            -=\\c`""""""" "` )                               #" << std::endl;
//	std::cout << "#               `~~~~~/ /~~`\                                #" << std::endl;
//	std::cout << "#                 -==/ /                                    #" << std::endl;
//	std::cout << "#                   '-'                                     #" << std::endl;
//	std::cout << "#                  _  _                                     #" << std::endl;
//	std::cout << "#                 ( `   )_                                  #" << std::endl;
//	std::cout << "#                (    )    `)                               #" << std::endl;
//	std::cout << "#              (_   (_ .  _) _)                             #" << std::endl;
//	std::cout << "#                                             _             #" << std::endl;
//	std::cout << "#                                            (  )           #" << std::endl;
//	std::cout << "#             _ .                         ( `  ) . )        #" << std::endl;
//	std::cout << "#           (  _ )_                      (_, _(  ,_)_)      #" << std::endl;
//	std::cout << "#         (_  _(_ ,)                                        #" << std::endl;
//	std::cout << "#############################################################" << std::endl;
//	Sleep(2000);
//}

void loadingPage() {
	int mid = getMidColumns();
	std::cout << "\n"; gotox(mid - 8);
	std::cout << "Loading...\n\n";
	gotox(mid - 8);
	std::cout << "[                   ] 0%\r";
	Sleep(100);
	gotox(mid - 8);
	std::cout << "[=                  ] 10%\r";
	gotox(mid - 8);
	Sleep(100);
	std::cout << "[==                 ] 20%\r";
	gotox(mid - 8);
	Sleep(100);
	std::cout << "[===                ] 30%\r";
	gotox(mid - 8);
	Sleep(100);
	std::cout << "[======             ] 40%\r";
	gotox(mid - 8);
	Sleep(100);
	std::cout << "[========           ] 50%\r";
	gotox(mid - 8);
	Sleep(100);
	std::cout << "[=========          ] 60%\r";
	gotox(mid - 8);
	Sleep(100);
	std::cout << "[==========         ] 70%\r";
	gotox(mid - 8);
	Sleep(100);
	std::cout << "[============       ] 80%\r";
	gotox(mid - 8);
	Sleep(100);
	std::cout << "[==============     ] 90%\r";
	gotox(mid - 8);
	Sleep(100);
	std::cout << "[===================] 100%\r";
	gotox(mid - 8);
	Sleep(100);
}

void loadingPageNotuse()
{
	int mid = getMidColumns();
	int x = mid-13;
	
	for (int i = 0; i < 9; i++)
	{
		system("cls");
		gotoxy(mid, 10);
		SetColor(7, 3);
		std::cout << "LOADING";
		SetColor(7, 0);

		gotoxy(x, 9);
		std::cout << "         _ \n";
		gotox(x);
		std::cout << "      -=\\`\\ \n";
		gotox(x);
		std::cout << "  |\\ ____\\_\\__  \n";
		gotox(x);
		std::cout << "  -=\\c`\"\"\"\"\"\"` )\n";
		gotox(x);
		std::cout << "    `~~~~~/ /~~`\   \n";
		gotox(x);
		std::cout << "      -==/ /        \n";
		gotox(x);
		std::cout << "        '-'\n";

		Sleep(200);
		x++;
	}
	SetColor(7, 0);
}

void drawHeader(std::string title) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	std::cout << std::endl << std::setw(70) << std::right << title << std::endl << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void drawDivider(int length, char character, int offset) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	std::cout << std::setw(offset) << std::setfill(' ') << " " << std::setfill(character) << std::setw(length) << "" << std::setfill(' ') << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void drawError(std::string message) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	std::cout << "Error: " << message << std::endl;
}

int getMidColumns() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);

	return csbi.dwSize.X/2;
}

void set_console_size(short x, short y)
{
	HANDLE hConsole;
	SMALL_RECT DisplayArea = { 0, 0, 100, 50 };

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	/*DisplayArea.Right = x;
	DisplayArea.Bottom = y;*/

	SetConsoleWindowInfo(hConsole, TRUE, &DisplayArea);
}
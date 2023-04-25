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
			if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
				std::cout << "*";
			}
			else {
				std::cout << " ";
			}
		}

	}
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
//	std::cout << "#            -=\\c`""""""" "`)                               #" << std::endl;
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
	std::cout << "\n"; gotox(getMidColumns() - 13 / 2);
	std::cout << "Loading...\n\n";
	gotox(getMidColumns()-27/2);
	std::cout << "[                    ] 0%\r";
	Sleep(100);

	gotox(getMidColumns()-27/2);
	std::cout << "[=                   ] 10%\r";
	Sleep(100);

	gotox(getMidColumns()-27/2);
	std::cout << "[==                  ] 20%\r";
	Sleep(100);

	gotox(getMidColumns()-27/2);
	std::cout << "[===                 ] 30%\r";
	Sleep(100);

	gotox(getMidColumns()-27/2);
	std::cout << "[====                ] 40%\r";
	Sleep(100);

	gotox(getMidColumns()-27/2);
	std::cout << "[=====               ] 50%\r";
	Sleep(100);

	gotox(getMidColumns()-27/2);
	std::cout << "[======              ] 60%\r";
	Sleep(100);

	gotox(getMidColumns()-27/2);
	std::cout << "[=======             ] 70%\r";
	Sleep(100);

	gotox(getMidColumns()-27/2);
	std::cout << "[========            ] 80%\r";
	Sleep(100);

	gotox(getMidColumns()-27/2);
	std::cout << "[=========           ] 90%\r";
	Sleep(100);

	gotox(getMidColumns()-27/2);
	std::cout << "[==========          ] 100%\r";
	Sleep(100);

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
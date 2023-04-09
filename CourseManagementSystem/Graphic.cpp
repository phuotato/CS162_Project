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
	coordinates.X = a;
	coordinates.Y = b;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void setColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void setBackgroundColor(int color) {
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color, color);
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
	gotoxy(15, 2); std::cout << " ____  ____  ____  __  _   _  ___  __  __  __  __  ___ " << "\n";
	gotoxy(15, 3); std::cout << "( ___)(_  _)(_  _)/  \\( )_( )/ __)(  \\/  )(  )(  )/ __)" << "\n";
	gotoxy(15, 4); std::cout << " )__)  _)(_   )( | ()/ ) _ (( (__  )    (  )(__)( \\__ \\" << "\n";
	gotoxy(15, 5); std::cout << "(__)  (____) (__) \\__ (_) (_)\\___)(_/\\/\\_)(______)(___/" << "\n";
}

void loadingPage() {
	std::cout << "#############################################################" << std::endl;
	std::cout << "#                    _                                      #" << std::endl;
	std::cout << "#                  -=\\`\\                                    #" << std::endl;
	std::cout << "#              |\\ ____\\_\\__                                 #" << std::endl;
	std::cout << "#            -=\\c`""""""" "`)                               #" << std::endl;
	std::cout << "#               `~~~~~/ /~~`\                                #" << std::endl;
	std::cout << "#                 -==/ /                                    #" << std::endl;
	std::cout << "#                   '-'                                     #" << std::endl;
	std::cout << "#                  _  _                                     #" << std::endl;
	std::cout << "#                 ( `   )_                                  #" << std::endl;
	std::cout << "#                (    )    `)                               #" << std::endl;
	std::cout << "#              (_   (_ .  _) _)                             #" << std::endl;
	std::cout << "#                                             _             #" << std::endl;
	std::cout << "#                                            (  )           #" << std::endl;
	std::cout << "#             _ .                         ( `  ) . )        #" << std::endl;
	std::cout << "#           (  _ )_                      (_, _(  ,_)_)      #" << std::endl;
	std::cout << "#         (_  _(_ ,)                                        #" << std::endl;
	std::cout << "#############################################################" << std::endl;
	Sleep(2000);
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
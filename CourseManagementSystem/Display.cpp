#include "Display.h"
using namespace std;

void gotoxy(short a, short b){
	COORD coordinates{};
	coordinates.X = a;
	coordinates.Y = b;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void setColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void drawHeader(){
	gotoxy(15, 2); cout << " ____  ____  ____  __  _   _  ___  __  __  __  __  ___ " << "\n";
	gotoxy(15, 3); cout << "( ___)(_  _)(_  _)/  \\( )_( )/ __)(  \\/  )(  )(  )/ __)" << "\n";
	gotoxy(15, 4); cout << " )__)  _)(_   )( | ()/ ) _ (( (__  )    (  )(__)( \\__ \\" << "\n";
	gotoxy(15, 5); cout << "(__)  (____) (__) \\__ (_) (_)\\___)(_/\\/\\_)(______)(___/" << "\n";
}

void drawBox(int x, int y, int width, int height) {
    for (int i = 0; i < height; i++) {
        gotoxy(x, y + i);
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                cout << "*";
            }
            else {
                cout << " ";
            }
        }
    }
}

void welcomePage()
{
    // set console size and title
    system("mode con: cols=90 lines=30");
    SetConsoleTitle(TEXT("CTDA Management Program"));

    //header
    drawHeader();
    
    //welcome message
    setColor(15); // white text color
    cout << "\n\n\n\n";
    drawBox(20, 10, 40, 8);
    gotoxy(32, 12);
    cout << "Welcome to";
    gotoxy(25, 14);
    setColor(9); // light blue text color
    cout << "FIT.HCMUS Management System.";
    setColor(15);

    // wait for user input to continue
    gotoxy(28, 24);
    cout << "Press any key to continue...";
    cin.get();

    // clear screen and display menu
    system("cls");
    cout << "\n\n\n\n";
    drawBox(20, 7, 35, 10);
    gotoxy(32, 8);
    cout << "Login as";
    gotoxy(25, 10);
    cout << "1. Staff";
    gotoxy(25, 12);
    cout << "2. Student";
    gotoxy(25, 14);
    cout << "0. Exit";
}
#include <iostream>
#include <Windows.h>

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
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

int main() {
    // set console size and title
    system("mode con: cols=80 lines=30");
    SetConsoleTitle(TEXT("CTDA Management Program"));

    //welcome message
    system("cls");
    setColor(15); // white text color
    std::cout << "\n\n\n\n";
    drawBox(20, 10, 40, 8);
    gotoxy(32, 12);
    std::cout << "Welcome to";
    gotoxy(25, 14);
    setColor(9); // light blue text color
    std::cout << "FIT.HCMUS Management System.";
    setColor(15);

    // wait for user input to continue
    gotoxy(28, 24);
    std::cout << "Press any key to continue...";
    std::cin.get();

    // clear screen and display menu
    system("cls");
    std::cout << "\n\n\n\n";
    drawBox(20, 7, 35, 10);
    gotoxy(32, 8);
    std::cout << "Login as";
    gotoxy(25, 10);
    std::cout << "1. Staff";
    gotoxy(25, 12);
    std::cout << "2. Student";

    return 0;
}

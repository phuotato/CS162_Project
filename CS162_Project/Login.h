#include <conio.h>
#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
void drawBox();
void login(string folder);
void gotoxy(short a, short b);
COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);
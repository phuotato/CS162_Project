#pragma once
#include "Universal.h"
using namespace std;

void drawHeader();
void welcomePage();
void loginPage();
void login(string folder);
COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);
void setcursor(bool visible, DWORD size);
void gotoxy(short a, short b);
#pragma once
#include <Windows.h>
#include <direct.h>
#include <conio.h>
#include <iomanip>
#include "Universal.h"

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);
void setcursor(bool visible, DWORD size);
void gotoxy(short a, short b);
void drawHeader();
void SetColor(int backgound_color, int text_color);
//void setColor(int color);
//void setBackgroundColor(int color);
void drawBox(int x, int y, int width, int height);
void loadingPage();

//0 = Black  8 = Gray
//1 = Blue   9 = Light Blue
//2 = Green  10 = Light Green
//3 = Aqua   11 = Light Aqua
//4 = Red    12 = Light Red
//5 = Purple 13 = Light Purple
//6 = Yellow 14 = Light Yellow
//7 = White 15 = Bright White

#pragma once
#include <Windows.h>
#include <direct.h>
#include <conio.h>
#include "Universal.h"

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);
void setcursor(bool visible, DWORD size);
void gotoxy(short a, short b);
void drawHeader();
void setColor(int color);
//void setBackgroundColor(int color);
void drawBox(int x, int y, int width, int height);
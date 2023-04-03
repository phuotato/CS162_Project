#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;

void gotoxy(short a, short b);
void drawHeader();
void welcomePage();
COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);
#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include "Universal.h"
using namespace std;

void gotoxy(short a, short b);
void drawHeader();
void welcomePage();
void loginPage();
void login(string folder);
COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);
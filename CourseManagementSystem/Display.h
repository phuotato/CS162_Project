#pragma once
#include <string>

int movingBarTutorial(int x, int y, int yp, int limitx, int limity, int steep, std::string* content);

int movingBar(int x, int y, int yp, int limitx, int limity, int steep, std::string* content); //input at the first row of the setting

void Tutorial(std::string*& content);

int YNQuestions(int x, int y, int size);

void Description(short range, short APages, short CPages, short Pcur);
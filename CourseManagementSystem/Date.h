#include "Universal.h"
#pragma once
class date
{
public:
	date(int Day, int Month, int Year);
	date();
	int getDay();
	int getMonth();
	int getYear();
private:
	int day;
	int month;
	int year;
};
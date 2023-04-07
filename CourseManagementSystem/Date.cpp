#include "Universal.h"
date::date(int Day, int Month, int Year) :day(Day), month(Month), year(Year) {}
date::date(){}
int date::getDay()
{
	return day;
}
int date::getMonth()
{
	return month;
}
int date::getYear()
{
	return year;
}
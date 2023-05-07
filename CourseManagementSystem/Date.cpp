#include "Date.h"
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
bool isLeap(int year)
{
    return (((year % 4 == 0) &&
        (year % 100 != 0)) ||
        (year % 400 == 0));
}
bool checkValidDate(int d, int m, int y)
{
    const int maxValid = 2023;
    const int minValid = 1900;

    if (y > maxValid || y < minValid)
        return false;
    if (m < 1 || m > 12)
        return false;
    if (d < 1 || d > 31)
        return false;

    if (m == 2)
    {
        if (isLeap(y))
            return (d <= 29);
        else
            return (d <= 28);
    }


    if (m == 4 || m == 6 ||
        m == 9 || m == 11)
        return (d <= 30);

    return true;
}
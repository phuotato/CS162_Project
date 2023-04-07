#include "Universal.h"
semester::semester(int Sem, int Day1, int Month1, int Year1, int Day2, int Month2, int Year2)
	:sem(Sem),startDate(Day1,Month1,Year1),endDate(Day2,Month2,Year2){}
semester::semester() {}
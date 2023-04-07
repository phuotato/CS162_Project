#pragma once
#include "Universal.h"
class semester
{
	public:
	semester(int Sem, int Day1, int Month1, int Year1, int Day2, int Month2, int Year2);
	semester();
	void addCourse();
	int getSem();
	semester* pNext;
	void getInformation();
private:
//	course* pHeadCourses = nullptr;
	date startDate; 
	date endDate;
	int sem;
};


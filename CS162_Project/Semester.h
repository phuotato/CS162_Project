#pragma once
#include "SchoolYear.h"
#include "Course.h"

class Semester 
{
private:
	int Sem;
	SchoolYear Year; //hay la dung int thoi?
	Date StartDate, EndDate;
	Course* CourseList;
public:
	void Create_Semester();
	void Delete_Semester();
};


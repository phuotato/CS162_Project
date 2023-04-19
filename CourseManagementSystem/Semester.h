#pragma once
#include "Universal.h"
#include "Course.h"
#include "Course.h"
class semester
{
	public:
	semester(int Sem, std::string StartDate, std::string EndDate );
	semester();
	int getSem();
	semester* pNext=nullptr;
	void getInformation();
	void addCourse();
	//Function create
private:
//	course* pHeadCourses = nullptr;
	std::string startDate; 
	std::string endDate;
	int sem;
	course* pHeadCourse = nullptr;
};


#pragma once
#include <string>
class semester
{
	public:
	semester(int Sem, std::string StartDate, std::string EndDate );
	semester();
	void addCourse();
	int getSem();
	semester* pNext;
	void getInformation();
private:
//	course* pHeadCourses = nullptr;
	std::string startDate; 
	std::string endDate;
	int sem;
};


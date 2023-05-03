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
	int sem;
	semester* pNext=nullptr;
	void getInformation();

	//Course function
	bool showCourse();
	void addCourse();
	void deleteCourse();
	void saveCoursetoFolder(std::string& name, std::string& id, std::string& className, std::string& lecturer, int& credit, int& maxStudent, std::string& weekDay, int& session, std::string& year, std::string& semester);
	void loadCourse();

	//Course pointer
	course* pHeadCourse = nullptr;
	course* pTailCourse = nullptr;
private:
	std::string startDate; 
	std::string endDate;

};


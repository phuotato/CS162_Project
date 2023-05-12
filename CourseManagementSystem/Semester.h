#pragma once
#include "Universal.h"
#include "Course.h"

class semester
{
public:
	semester(int Sem, std::string StartDate, std::string EndDate);
	semester();

	//use const to indicate that these don't modify the class state
	int getSem();
	void getInformation(); 

	int sem;
	semester* pNext=nullptr;

	//Show function
	bool viewCourse();
	void showingCourseList(course* pHead);
	void showCourses(course*& pHead, short range, short& Pcur);
	int getAllCourses(course* pHead);
	void showPCourses(course*& pHead, short range, short& Pcur);

	//Course function
	
	void addCourse();
	void deleteCourse();
	void saveCoursetoFolder(const std::string& name, const std::string& id, const std::string& className, const std::string& lecturer, int credit, int maxStudent, const std::string& weekDay, int session, const std::string& year, const std::string& semester);
	void loadCourse();

	//Course pointer
	course* pHeadCourse = nullptr;
	course* pTailCourse = nullptr;
private:
	std::string startDate; 
	std::string endDate;

};


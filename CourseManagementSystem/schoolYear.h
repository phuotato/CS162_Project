#pragma once
#include "Semester.h"
#include "Student.h"

class schoolYear
{
public:
	//Constructor
	schoolYear(std::string time, schoolYear* pointer);
	schoolYear();

	//Get attribute
	std::string getYear();

	//Functions
	//Create function
	void createSchoolYear();
	bool checkCorrectYear(std::string year);
	bool checkExistSchoolYear(std::string year);
	void createSemester();
	bool checkExistSemester(int sem);
	bool checkCorrectSemester(std::string year);
	schoolYear* findSchoolYear(std::string year);
	
	//Load File Function
	void loadFile();
	//Load all created semester of specific schoolyear
	void loadFile(std::string year);

	//Delete function
	void deleteSchoolYear();

	//Show SchoolYear
	void showSchoolYear();

	//Create&Information_Class
	bool checkExistClass(std::string Name);
	void addNewClass();
	void createInformationClass();

	//Pointer
	schoolYear* pNext = nullptr;

	//Class pointer
	Class* pHeadClass;
	Class* pTailClass;

	//Semester pointer
	semester* pHeadSemester = nullptr;
	semester* pTailSemester = nullptr;

private:
	std::string year; 
	
};
void switchSchoolYear();
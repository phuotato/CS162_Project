#pragma once
#include "Semester.h"
#include "Student.h"

class schoolYear
{
public:
	std::string year;

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
	bool checkWhetherSmall();
	void createSemester();
	bool checkExistSemester(int sem);
	bool checkCorrectSemester(std::string year);
	bool checkAvaiSemester();
	void increaseSem();
	schoolYear* findSchoolYear(std::string year);
	
	//Load File Function
	void loadFile();
	//Load all created semester of specific schoolyear
	void loadFile(std::string year);

	//Delete function
	void deleteSchoolYear();

	//Show SchoolYear
	void showSchoolYear();

	//Pointer
	schoolYear* pNext = nullptr;

	//Semester pointer
	semester* pHeadSemester = nullptr;
	semester* pTailSemester = nullptr;

private:
	int numSem = 0;
	
};
void switchSchoolYear();
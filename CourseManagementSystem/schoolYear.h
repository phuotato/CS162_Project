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
	int getAllSchoolYear();

	//Functions
	//Create function
	void createSchoolYear(short& k);
	bool checkCorrectYear(std::string year);
	bool checkExistSchoolYear(std::string year);
	void chooseSchoolYear(short& k);
	bool createSemester();
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
	void showSchoolYearAll(short range, short& Pcur);
	void showP(short range, short& Pcur);
	void ShowingList();

	//Show semester
	bool showSemester();
	//Pointer
	schoolYear* pNext = nullptr;

	//Semester pointer
	semester* pHeadSemester = nullptr;
	semester* pTailSemester = nullptr;

private:
	int numSem = 0;
	
};
void switchSchoolYear();
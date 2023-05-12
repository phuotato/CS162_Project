#pragma once
#include "Semester.h"
#include "Student.h"

class schoolYear
{
public:
	std::string year;

	// Constructor
	schoolYear(std::string time, schoolYear* pointer);
	schoolYear();

	// Getters
	std::string getYear();
	int getAllSchoolYear();

	// Functions
	bool checkCorrectSemester(std::string year); //This function is no where be found???

	void createSchoolYear(short& k);
	bool checkCorrectYear(const std::string& year);
	bool checkExistSchoolYear(const std::string& year);
	void chooseSchoolYear(short& k);
	bool createSemester();
	bool checkExistSemester(int sem);
	bool checkAvaiSemester();
	void increaseSem();
	schoolYear* findSchoolYear(const std::string& year);
	void loadFile();

	//Load all created semester of specific schoolyear
	void loadFileSemester(std::string year);

	//Delete function
	void deleteSchoolYear();
	void showSchoolYearAll(short range, short& Pcur);
	void showP(short range, short& Pcur);
	void ShowingList();
	bool showSemester();

	// Pointer
	schoolYear* pNext = nullptr;

	// Semester pointer
	semester* pHeadSemester = nullptr;
	semester* pTailSemester = nullptr;

private:
	int numSem = 0;
};

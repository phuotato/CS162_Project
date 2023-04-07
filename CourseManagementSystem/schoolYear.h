#pragma once
#include "Universal.h"

class Class
{
public:
	//Constructor
	Class(std::string Name);
	Class();
	//Get attribute
	std::string getName();

	//Function for class
	void deleteClass();

	//Pointer
	Class* pNext;

private:
	std::string Name;
};

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
	void loadFile();
	void createSchoolYear();
	bool checkCorrectYear(std::string year);
	bool checkExistSchoolYear(std::string year);

	void createSemester();
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

private:
	std::string year;
};
void switchSchoolYear();
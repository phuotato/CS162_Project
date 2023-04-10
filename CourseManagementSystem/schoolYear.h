#pragma once
#include "Semester.h"
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
	void LoadFile(std::string curYear);
	void Choices();
	
	//Minor function
	bool CheckClasses(std::string curName, std::string curYear);

	//Pointer
	Class* pNext=nullptr;

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
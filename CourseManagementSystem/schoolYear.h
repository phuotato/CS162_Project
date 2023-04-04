#pragma once
#include <string>

class Class
{
public:
	//Constructor
	Class(std::string Name);
	Class();
	//Get attribute
	std::string getName();


	//Pointer
	Class* pNext;

private:
	std::string Name;
};

class SchoolYear
{
public:
	//Constructor
	SchoolYear(std::string time, SchoolYear* pointer);
	SchoolYear();

	//Get attribute
	std::string getYear();

	//Functions
	//Create function
	void loadFile();
	void createSchoolYear();
	bool checkExistSchoolYear(std::string year);

	//Delete function
	void deleteSchoolYear();

	//Show SchoolYear
	void showSchoolYear();

	//Create&Information_Class
	void Create_Information_Class();

	//Pointer
	SchoolYear* pNext = nullptr;

	//Class pointer

	Class* pHeadClass;
	Class* pTailClass;

	//Semester pointer


private:
	std::string year;
};

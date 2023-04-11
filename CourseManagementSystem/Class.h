#pragma once
#include "Universal.h"
#include "Student.h"
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
	void LoadFile();
	void Choices();
	//void getOption();
	//void addStudentto1stClass_Console();
	//void addStudentto1stClass_File();
	void addNewClass();
	void createInformationClass();
	
	//Minor function
	bool CheckClasses(std::string curName);
	bool checkExistClass(std::string Name);

	//Pointer
	Class* pNext = nullptr;

private:
	std::string Name;
	student* headS = nullptr;
};
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
	void LoadFile(std::string curYear);
	void Choices();
	void getOption();
	void addStudentto1stClass_Console();
	void addStudentto1stClass_File();
	//Minor function
	bool CheckClasses(std::string curName, std::string curYear);

	//Pointer
	Class* pNext = nullptr;

private:
	std::string Name;
	student* headS = nullptr;
};
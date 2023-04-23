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
	void getOption();		// option to add students
	void deleteStudentList();
	void addStudentto1stClass_Console();
	void exportNewStudentProfile(std::string classcode, std::string id, std::string firstname, std::string lastname, int no, bool gender, int day, int month, int year, std::string socialID);
	void addStudentto1stClass_File();
	void loadStudent();
	bool checkClassInfo(std::string classcode);
	void sortStudentsLexicographically(std::string classcode);
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
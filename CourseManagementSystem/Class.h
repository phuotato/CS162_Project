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
	void addNewClass();
	int getAllClass();
	bool checkLatestYear();

	//Function show for class
	void showClassList(short range, short& Pcur);
	void showP(short range, short& Pcur);
	void showingList();

	//Function for students
	void getOption();		// option to add students
	void deleteStudentList();
	void addStudentto1stClass_Console();
	void exportNewStudentProfile(std::string classcode, std::string id, std::string firstname, std::string lastname, int no, bool gender, int day, int month, int year, std::string socialID);
	void addStudentto1stClass_File();
	void loadStudent();
	void sortStudentsLexicographically(std::string classcode);

	//View Students
	void viewStudentList();
	void showingStudentList(student* pHead);
	void showStudents(student*& pHead, short range, short& Pcur);
	int getAllStudents(student* pHead);
	void showPStudents(student*& pHead, short range, short& Pcur);

	//Minor function
	bool CheckClasses(std::string curName);
	bool checkExistClass(std::string Name);
	bool checkClassInfo(std::string classcode);

	//Pointer
	Class* pNext = nullptr;

private:
	std::string Name;
	student* headS = nullptr;
};
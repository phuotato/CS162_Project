#pragma once
#include "Universal.h"
#include "Date.h"

class student
{
public:

	student(int No, std::string id, std::string firstName, std::string lastName, bool gender, date dob, std::string socialId, student* pointer);

	student* pNext = nullptr;
	student* pStudent = nullptr;

	//Constructor
	student(int no, std::string id, std::string firstname, std::string lastname, bool gender, int day, int month, int year, std::string socialId, student* pointer) :
		no(no), id(id), firstName(firstname), lastName(lastname), gender(gender),
		dob(day, month, year), socialId(socialId), pNext(pointer) {}
	void addStudentto1stClass_Console(student*& headS);
	void addStudentto1stClass_File(student*& headS);
	void viewProfile(student*& headS);
	void deleteStudentList(student*& headS);
private: 
	int no;
	std::string id, firstName, lastName, socialId;
	bool gender;
	date dob;
	student* headS = nullptr;
};


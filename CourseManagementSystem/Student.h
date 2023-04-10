#pragma once
#include <string>
#include "Date.h"
using namespace std;

class student
{
public:

	student(int No, string id, string firstName, string lastName, bool gender, date dob, string socialId, student* pointer);

	student* pNext = nullptr;
	student* pStudent = nullptr;

	//Constructor
	student(int no, string id, string firstname, string lastname, bool gender, int day, int month, int year, string socialId, student* pointer) :
		no(no), id(id), firstName(firstname), lastName(lastname), gender(gender),
		dob(day, month, year), socialId(socialId), pNext(pointer) {}
	void addStudentto1stClass_Console(student*& headS);
	void addStudentto1stClass_File(student*& headS);
	void viewProfile(student*& headS);
	void deleteStudentList(student*& headS);
private: 
	int no;
	string id, firstName, lastName, socialId;
	bool gender;
	date dob;
	student* headS = nullptr;
};


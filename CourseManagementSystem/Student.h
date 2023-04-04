#pragma once
#include <string>
#include "Date.h"
using namespace std;

class student
{
public:
//	student(int No, string id, string firstName, string lastName, bool gender, Date dob, string socialId, student* pointer);
	int no;
	string id, firstName, lastName, socialId;
	bool gender;
	Date dob;
	student* pNext = nullptr;
	student* pStudent = nullptr;

	//Constructor
	student(int no, string id, string firstname, string lastname, bool gender, Date dob, string socialId, student* pointer) :
		no(no), id(id), firstName(firstname), lastName(lastname), gender(gender),
		dob(dob), socialId(socialId), pNext(pointer) {}
	void addStudentto1stClass(student*& headS);
	void viewProfile(student*& headS);
	void deleteStudentList(student*& headS);
private: 
	student* headS = nullptr;
};


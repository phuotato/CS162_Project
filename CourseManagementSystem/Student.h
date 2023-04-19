#pragma once
#include "Universal.h"
#include "Date.h"

class student
{
private:
	int no;
	std::string id, firstName, lastName, socialId;
	bool gender;
	date dob;

public:
	//ua cai cho nay de lam gi nua z mn?
	//student(int No, std::string id, std::string firstName, std::string lastName, bool gender, date dob, std::string socialId, student* pointer);

	student* pNext = nullptr;
	student* pStudent = nullptr;

	//Constructor
	student(){}
	student(int no, std::string id, std::string firstname, std::string lastname, bool gender, int day, int month, int year, std::string socialId, student* pointer) :
		no(no), id(id), firstName(firstname), lastName(lastname), gender(gender),
		dob(day, month, year), socialId(socialId), pNext(pointer) {}

	void viewProfile(student*& headS);
	void deleteStudentList(student*& headS);


};


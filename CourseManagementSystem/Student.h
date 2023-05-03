#pragma once
#include "Universal.h"
#include "Date.h"

//std::ifstream Classin("Data/Class");
//std::ifstream Processin("Data/schoolYear/



class student
{
private:
	int no;
	std::string id, firstName, lastName, socialId;
	bool gender;
	date dob;

public:
	
	
	student* pNext = nullptr;
	student* pStudent = nullptr;

	//Constructor
	student(){}
	student(int no, std::string id, std::string firstname, std::string lastname, bool gender, int day, int month, int year, std::string socialId, student* pointer) :
		no(no), id(id), firstName(firstname), lastName(lastname), gender(gender),
		dob(day, month, year), socialId(socialId), pNext(pointer) {}
	// Function
	void viewProfile_Staff();
	void viewProfile_Student(std::string username);
	bool checkExistFile(std::string id);

	std::string getStudentID()
	{
		return id;
	}
	std::string getFirstName()
	{
		return firstName;
	}
	std::string getLastName()
	{
		return lastName;
	}
};
#pragma once
#include "Universal.h"
#include "Date.h"

class student
{
private:
	int no;
	std::string id, firstName, lastName, socialId, Date;
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
	student(int no, std::string id, std::string firstname, std::string lastname, bool gender, std::string dob, std::string socialId);
	// Function
	void viewProfile();
	bool checkExistFile(std::string id);

	std::string getStudentID()
	{
		return id;
	}
	int getNo()
	{
		return no;
	}
	std::string getFirstName()
	{
		return firstName;
	}
	std::string getLastName()
	{
		return lastName;
	}
	std::string getSocialId()
	{
		return socialId;
	}
	std::string getDate()
	{
		return Date;
	}
	bool getGender()
	{
		return gender;
	}
};


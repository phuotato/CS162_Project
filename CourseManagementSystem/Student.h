#pragma once
#include "Universal.h"
#include "Date.h"

//std::ifstream Classin("Data/Class");
//std::ifstream Processin("Data/schoolYear/

class student
{
private:
	int no;
	std::string id, firstName, lastName, socialId, dat;
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
	student(int no, std::string id, std::string firstname, std::string lastname, bool gender, std::string dob, std::string socialId) :
		no(no), id(id), firstName(firstname), lastName(lastname), gender(gender),
		dat(dob), socialId(socialId){}
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
	int getNo()
	{
		return no;
	}
	void increaseNo()
	{
		no += 1;
	}
	bool getGender()
	{
		return gender;
	}
	std::string getDate()
	{
		return dat;
	}
	std::string getSocialId()
	{
		return socialId;
	}
};


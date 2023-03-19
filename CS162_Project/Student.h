#pragma once
#include "Universal.h"
class Student
{
public: 
	//attribute
	int No;
	string ID;
	string firstname, lastname;
	bool Gender; //0 for male, 1 for female
	Date DOB;
	string Social_ID;
	Student* pNext;
	
	//function
	void view_Course();
	void view_Score();
	
};



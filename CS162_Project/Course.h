#pragma once
#include "Student.h"
#include "Class.h"

class Course
{
private:
	string ID;
	string course_name;
	string class_name;
	string lecturer;
	int credits;
	int max_student = 50;
	string day, session;
	//(MON / TUE / WED / THU / FRI / SAT
	//S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30))
	Class* StudentList;
	Course* pNext;

public:
	//function
	void Add_Course();
	void Delete_Course();
	void View_Course();
	void Update_Course();

};

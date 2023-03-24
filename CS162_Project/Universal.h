#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Date {
	int day;
	int month;
	int year;
};

class Student {
public:
	//attribute
	int No;
	string ID;
	string firstname, lastname;
	bool Gender; //0 for male, 1 for female
	Date DOB;
	string Social_ID;
	Course* CourseList;

	Student* pNext;

	//Constructor
	Student();

	//function	
	void viewProfile(Student*& student, string username);
	void view_Course();
	void view_Score();
};

class Class {
public:
	//a linked list of student
	Student* headS;

	//Constructor
	Class();

	//function
	void Add_Student(std::ifstream& fin, std::string username, Student*& student);
	void Remove_Student();
	void deleteStudentList(Student*& student);
};

class Course {
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
	Class StudentList;

public:
	Course* pNext;
	//Constructor
	Course();
	//function
	void Add_Course();
	void Delete_Course();
	void View_Course();
	void Update_Course();
	void Export_Class(string filename);
	void Import_Scoreboard(string filename);

};

class Semester
{
private:
	int Sem;
	SchoolYear Year; //hay la dung int thoi?
	Date StartDate, EndDate;
	Course* CourseList;
public:
	//Constructor
	Semester();
	//Function
	void Create_Semester();
	void Delete_Semester();
};


class SchoolYear
{
private:
	Semester* SemList; //dynamic array
	Class* ClassList; //linked list 

public:
	//Constructor
	SchoolYear();

	//Function
	void Create_SchoolYear();
	void delete_SchoolYear();

	// Classes section
	void Add_Classes();
};





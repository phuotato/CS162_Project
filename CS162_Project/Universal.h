#pragma once
#include <iostream>
#include <string>
using namespace std;
typedef void type;

struct Date {
	int day;
	int month;
	int year;
};

struct Student {
	int No, ID;
	string firstname, lastname;
	bool Gender; //0 for male, 1 for female
	Date DOB;
	int Social_ID;
} *headS;

//se quyet dinh nen de class nay trong file nao sau
class courseLL {
private:
	struct Course {
		string ID;
		string course_name;
		string class_name;
		string lecturer;
		int credits;
		int max_student = 50;
		string day, session;
		//(MON / TUE / WED / THU / FRI / SAT
		//S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30))
		Student* student_list;
		Course* pNext;
	} *headC;

public:
	//cac function nhu add course & add student, etc
};

type Staff()
{
	system("cls");
	cout << "Begin of school year: \n";
	// goi cac function Create a school year, classes, Add students o day
}
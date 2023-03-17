#pragma once
struct Date {
	int day;
	int month;
	int year;
};

struct Student {
	int No, ID;
	std::string firstname, lastname;
	bool Gender; //0 for male, 1 for female
	Date DOB;
	int Social_ID;
} *headS;

class courseLL {
private:
	struct Course {
		std::string ID;
		std::string course_name;
		std::string class_name;
		std::string lecturer;
		int credits;
		int max_student = 50;
		std::string day, session;
		//(MON / TUE / WED / THU / FRI / SAT
		//S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30))
		Student* student_list;
		Course* pNext;
	} *headC;

public:
	//cac function nhu add course & add student, etc
};

void input_Date(Date cur_Date);
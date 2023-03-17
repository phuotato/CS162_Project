#pragma once
#include "Universal.h"

class SchoolYear
{
private:
	struct Semester_LL {
		int subsemester; //1 2 3
		Date start_Date; //each year has different semester - not the start one (school_Year_LL)
		Date end_Date;
		Semester_LL* pNext;
	};

	struct classes_LL {
		char program[5]; //E.g: APCS, CLC, VP
		int year; //19 20 21 22
		int subclass; //1 2 3
		classes_LL* pNext;
		Semester_LL* first_Semester;	//Connect the semester and classes
	};

	struct school_Year_LL {
		int year;
		school_Year_LL* pNext;
		classes_LL* first_Read;	// The year points to the first class created
	};

public:
	void input_New_Year(school_Year_LL*& pHead, school_Year_LL*& pLast);

	void delete_Data(school_Year_LL* pHead);

	// Classes section
	void input_Classes(school_Year_LL* pHead);


	// Semester section
	void input_Semester(classes_LL* pHead);
};


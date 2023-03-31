#include "Universal.h"
using namespace std;

// definition constructors

//SchoolYear::SchoolYear(int cYear, Semester*& cSemList, Class*& cClassList, SchoolYear* pHead) : SYear(cYear), SemList(cSemList), 
//						ClassList(cClassList) 
//{
//	cin >> cYear;
//
//	if (!cSemList) {
//		Semester generalSemester;
//		generalSemester.Create_Semester(cSemList);
//	}
//
//
//	if (!cClassList) {
//		cClassList = new Class(cClassList->Year, cClassList->Name, cClassList->Subclass, cClassList->HeadS);
//	}
//	else {
//		Class* tmp = cClassList;
//		cClassList = new Class(cClassList->Year, cClassList->Name, cClassList->Subclass, cClassList->HeadS);
//		cClassList->pNext = tmp;
//	}
//}
//
//
//
////School year section
////void SchoolYear::Create_SchoolYear() 
////{
////	std::cout << "New year: ";
////	if (pHead) {																		// If there is already one - create a new
////		pLast->pNext = new school_Year_LL;												// Then create the one after the first through the last
////		std::cin >> pLast->pNext->year;
////		pLast->pNext->pNext = nullptr;
////		pLast = pLast->pNext;															// Make sure the last points to the last
////		return;																			// Finally, return.
////	}
////	else {																				// Create the first one
////		pHead = new school_Year_LL;
////		std::cin >> pHead->year;
////		pHead->pNext = nullptr;
////		pLast = pHead;
////		return;
////	}
////}																						// After input - select to create new classes
////
////void SchoolYear::delete_Data(school_Year_LL* pHead) 
////{
////	while (pHead) {
////		school_Year_LL* cur = pHead->pNext;
////		delete pHead;
////		pHead = cur;
////	}
////}
////
////
//////Classes section
////
////void SchoolYear::input_Classes(school_Year_LL* pHead) 
////{												
////	// A new year is need to input class
////	classes_LL* cur = pHead->first_Read;
////	bool check = true;
////	char k;
////	while (check) {
////		for (; cur; cur = cur->pNext);
////		cur = new classes_LL;
////		cur->year = pHead->year % 100;													// The class itself in the year
////
////		std::cout << "Which program this class?(Ex: APCS, CLC,...) \nYour answer: ";	// Input program
////		std::cin.get(cur->program, 5, '\n');
////		std::cin.ignore();
////
////		std::cout << "Which subclass of this class? (Ex: 1, 2, 3,...) \nYour answer: ";	// Input subclass
////		std::cin >> cur->subclass;
////
////		std::cout << "Do you want to input more classes? \nY/N: ";						// Input more classes
////		std::cin >> k;
////		while (k != 'Y' && k != 'N') {
////			std::cout << "You have entered wrong! Try again!\nY/N: ";					// Make sure the user input correctly
////			std::cin >> k;
////		}
////
////		if (k == 'N') {																	// If no - end the list and get out
////			cur->pNext = nullptr;
////			return;
////		}
////
////	}
////
////
////}
//
//
//
bool schoolYear::createSemester()
{
	cout << "What is semester you want to create: ";
		int x; cin >> x;
		while (arrSemester[x - 1])
		{
			cout << "This semester is already created. Please try again others.\n";
			cin >> x;
		}
		cout << "Invalid semsester.\n";
		cout << "Enter the start date of the semester:\n";
		cout << "Day: "; int day1; cin >> day1;
		cout << "Month: "; int month1; cin >> month1;
		cout << "Year: "; int year1; cin >> year1;
		cout << "Enter the end date of the semester:\n";
		cout << "Day: "; int day2; cin >> day2;
		cout << "Month: "; int month2; cin >> month2;
		cout << "Year: "; int year2; cin >> year2;
		arrSemester[x - 1] = new semester(x, day1, month1, year1, day2, month2, year2);
		return true;
}
schoolYear::schoolYear(string time, schoolYear* pointer) :year(time) , pNext(pointer){}
schoolYear::schoolYear() {}
date::date(int Month, int Day, int Year):month(Month),day(Day),year(Year){}
semester::semester(int Sem, int Day1, int Month1, int Year1, int Day2, int Month2, int Year2)
	:sem(Sem),startDate(Day1,Month1,Year1),endDate(Day2,Month2,Year2){}
void school::createSchoolYear()
{
	if (!pHeadSchoolYear)
	{
		cout << "Enter your school year you want to create: ";
		string year; getline(cin, year);
		pHeadSchoolYear = new schoolYear(year, nullptr);
		cout << "Create succesfully.\n";
		pTailSchoolYear = pHeadSchoolYear;
	}
	else
	{
		cout << "Enter your school year you want to create: ";
		string year; getline(cin, year);
		schoolYear* tmp = new schoolYear(year, nullptr);
		pTailSchoolYear->pNext = tmp;
		pTailSchoolYear = tmp;
	}
	cout << "Create succesfully.\n";
	cout << "Do you want to add more school year:(Y/N || y/n) ";
	char choice; cin >> choice;
	if (choice == 'Y' || choice == 'y')
		createSchoolYear();
	else
		return;
}
string schoolYear::getYear()
{
	return year;
}
void school::createSemesterFromSchoolYear()
{
	cout << "Enter schoolyear include your create semester: ";
	string year; getline(cin, year);
	schoolYear* cur = pHeadSchoolYear;
	for (; cur; cur = cur->pNext)
	{
		string tmp = cur->getYear();
		if (tmp == year);
	}
	if (cur->createSemester())
		cout << "Create semester successfully.\n";
	cout << "Do you want to add more semester:(Y/N || y/n) ";
	char choice; cin >> choice;
	if (choice == 'Y' || choice == 'y')
		createSchoolYear();
	else
		return;
}
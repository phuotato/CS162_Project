#include "Universal.h"
using namespace std;

// definition constructors

SchoolYear::SchoolYear(int cYear, Semester*& cSemList, Class*& cClassList, SchoolYear* pHead) : SYear(cYear), SemList(cSemList), 
						ClassList(cClassList) 
{
	cin >> cYear;

	if (!cSemList) {
		Semester generalSemester;
		generalSemester.Create_Semester(cSemList);
	}


	if (!cClassList) {
		cClassList = new Class(cClassList->Year, cClassList->Name, cClassList->Subclass, cClassList->HeadS);
	}
	else {
		Class* tmp = cClassList;
		cClassList = new Class(cClassList->Year, cClassList->Name, cClassList->Subclass, cClassList->HeadS);
		cClassList->pNext = tmp;
	}
}



//School year section
//void SchoolYear::Create_SchoolYear() 
//{
//	std::cout << "New year: ";
//	if (pHead) {																		// If there is already one - create a new
//		pLast->pNext = new school_Year_LL;												// Then create the one after the first through the last
//		std::cin >> pLast->pNext->year;
//		pLast->pNext->pNext = nullptr;
//		pLast = pLast->pNext;															// Make sure the last points to the last
//		return;																			// Finally, return.
//	}
//	else {																				// Create the first one
//		pHead = new school_Year_LL;
//		std::cin >> pHead->year;
//		pHead->pNext = nullptr;
//		pLast = pHead;
//		return;
//	}
//}																						// After input - select to create new classes
//
//void SchoolYear::delete_Data(school_Year_LL* pHead) 
//{
//	while (pHead) {
//		school_Year_LL* cur = pHead->pNext;
//		delete pHead;
//		pHead = cur;
//	}
//}
//
//
////Classes section
//
//void SchoolYear::input_Classes(school_Year_LL* pHead) 
//{												
//	// A new year is need to input class
//	classes_LL* cur = pHead->first_Read;
//	bool check = true;
//	char k;
//	while (check) {
//		for (; cur; cur = cur->pNext);
//		cur = new classes_LL;
//		cur->year = pHead->year % 100;													// The class itself in the year
//
//		std::cout << "Which program this class?(Ex: APCS, CLC,...) \nYour answer: ";	// Input program
//		std::cin.get(cur->program, 5, '\n');
//		std::cin.ignore();
//
//		std::cout << "Which subclass of this class? (Ex: 1, 2, 3,...) \nYour answer: ";	// Input subclass
//		std::cin >> cur->subclass;
//
//		std::cout << "Do you want to input more classes? \nY/N: ";						// Input more classes
//		std::cin >> k;
//		while (k != 'Y' && k != 'N') {
//			std::cout << "You have entered wrong! Try again!\nY/N: ";					// Make sure the user input correctly
//			std::cin >> k;
//		}
//
//		if (k == 'N') {																	// If no - end the list and get out
//			cur->pNext = nullptr;
//			return;
//		}
//
//	}
//
//
//}
#include "Semester.h"
#include "schoolYear.h"
//extern schoolYear* pHeadSchoolYear;
//std::ifstream fin;
//std::ifstream fout;
semester::semester(int Sem, std::string StartDate, std::string EndDate)
	:sem(Sem), startDate(StartDate), endDate(EndDate) {}
semester::semester() {}
//void semester::addCourse()
//{
//	std::cout << "Enter the schoolyear: ";
//	std::string year; getline(std::cin, year);
//	pHeadSchoolYear->checkCorrectYear(year);
//}
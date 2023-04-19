#pragma once
#include "SchoolYear.h"
#include "Universal.h"
#include "Graphic.h"
#include "Class.h"
std::ifstream fin;
std::ofstream fout;

//Initialize extern variables
extern schoolYear* curSchoolYear;
extern schoolYear* pHeadSchoolYear;
extern schoolYear* pTailSchoolYear;

extern Class* pHeadClass;
extern Class* pTailClass;
extern Class* curClass;

//Constructor for SchoolYear
schoolYear::schoolYear(std::string time, schoolYear* pointer) :year(time), pNext(pointer) {}
schoolYear::schoolYear() {}

//Create SchoolYear

void schoolYear::createSchoolYear()
{
	std::cin.ignore();
	loadFile();
	bool flag = 1;
	while (true)
	{
		system("cls");
		showSchoolYear();
		std::cout << "\n\n\n\t\tWould you like to create a new school year? (Y/N): ";
		char option;
		std::cin >> option;
		std::cin.ignore();

		if (option == 'Y' || option == 'y')
		{
			std::cout << "\t\tEnter new school year (e.g. 2022-2023): ";
			std::string year; getline(std::cin, year);

			//checking condition
			if (checkCorrectYear(year) == false) {
				std::cout << "Please enter the correct year!\n";
				system("pause");
				system("cls");
				continue;
			}

			if (checkExistSchoolYear(year) != 0)
			{
				//Create a new schoolyear and store in linked list
				fout.open("../Data/School Year/all school year.txt", std::ios::app);				//Open file stored all year of school
				fout << std::endl;
				fout << year;			//Write down the schoolyear
				fout.close();

				//Check folder and write down information for the schoolyear
				if (_mkdir(("../Data/School Year/" + year).c_str()));
				fout.open("../Data/School Year/" + year + "/all semester.txt", std::ios::app);
				fout.close();

				if (!pHeadSchoolYear) pHeadSchoolYear = new schoolYear(year, nullptr);
				schoolYear* tmp = pHeadSchoolYear->pNext;
				tmp = new schoolYear(year, nullptr);
				pTailSchoolYear->pNext = tmp;
				pTailSchoolYear = tmp;
				if (!pHeadSchoolYear) pHeadSchoolYear = pTailSchoolYear;
				flag = 1;
			}
			else
			{
				std::cout << "This school year is already created, please enter another school year\n";
				flag = 0;
			}
			if (flag == 1)
			{
				std::cout << "Created succesfully\n";
				system("pause");
				return;
			}
		}
		else return;
	}
	
}

void schoolYear::loadFile()
{
	fin.open("../Data/School Year/all school year.txt");
	while (!fin.eof())
	{
		std::string year;
		getline(fin, year);
		if (year == "")																		//Check if the file is empty or not
			break;
		if (!pHeadSchoolYear)
		{
			pHeadSchoolYear = new schoolYear(year, nullptr);
			pTailSchoolYear = pHeadSchoolYear;
		}
		else
		{
			schoolYear* tmp = new schoolYear(year, nullptr);
			pTailSchoolYear->pNext = tmp;
			pTailSchoolYear = tmp;
		}
	}
	fin.close();
}

bool schoolYear::checkExistSchoolYear(std::string year)
{
	if (pHeadSchoolYear)
	{
		for (schoolYear* cur = pHeadSchoolYear; cur; cur = cur->pNext)
		{
			if (cur->getYear() == year)
				return 0;
		}
	}
	return 1;
}

bool schoolYear::checkCorrectYear(std::string year) {
	int length = year.length();
	if (length != 9) return false;
	for (int i = 0; i < 4; i++) {
		if (year[i] < '0' || year[i] > '9' || year[i + 5] > '9' || year[i + 5] < '0') return false;
	}
	if (year[4] != '-') return false;
	if (year[8] - year[3] == -9);
	else if (year[8] - year[3] != 1) return false;

	return true;
}


//Delete SchoolYear


void schoolYear::deleteSchoolYear()
{
	for (pHeadSchoolYear; pHeadSchoolYear;)
	{
		schoolYear* tmp = pHeadSchoolYear->pNext;
		delete pHeadSchoolYear;
		pHeadSchoolYear = tmp;

	}
}


//Show SchoolYear

void schoolYear::showSchoolYear()
{
	gotoxy(30, 3);
	std::cout << "Created School Years\n";
	std::cout << "\n\t\t+--------------------------------------------------+";
	for (schoolYear* cur = pHeadSchoolYear; cur; cur = cur->pNext)
	{
		std::cout << "\n\t\t|                 " << cur->getYear() << "                        |";
	}
	std::cout << "\n\t\t+--------------------------------------------------+";
}



//Other functions

std::string schoolYear::getYear()
{
	return year;
}
void schoolYear::createSemester()
{
	char x;
	bool flag = 0;
	std::string year;
	schoolYear* cur;
	loadFile();
	std::cin.ignore();
	while (true)
	{
		//std::cout << "\n\t\tEnter school year include your semester:";
		std::cout << "\n\t\tEnter school year:";
		getline(std::cin, year);
		if (!checkCorrectYear(year))
		{
			std::cout << "Invalid school year. Try other ones\n";
			continue;
		}
		cur = findSchoolYear(year);
		if (!cur)
		{
			std::cout << "This school year don't exist. Try other ones\n";
			continue;
		}
		break;
	}
	cur->loadFile(year);
	while (true)
	{
		std::cout << "What is semester you want to create: ";
		while (true)
		{
			std::cout << "Sem:";
			std::cin >> x;
			if ('x' < 1 || x > '3')
			{
				std::cout << "Invalid semester. Try other ones\n";
				continue;
			}
			if (cur->checkExistSemester(x - '0'))
			{
				std::cout << "This semester was already created. Try other ones\n";
				continue;
			}
			break;
		}
		fout.open("../Data/School Year/" + year + "/all semester.txt", std::ios::app);			//Open file stored all semester of that year
		fout << "Semester " << x << std::endl;														//Write down the semester
		fout.close();
		std::cout << "Enter the start date: ";
		std::string StartDate;
		std::cin.ignore();
		getline(std::cin, StartDate);
		std::cout << "Enter the end date: ";
		std::string EndDate;
		std::cin.ignore();
		getline(std::cin, EndDate);
		std::string sem;
		sem += x;
		if (_mkdir(("../Data/School Year/" + year + "/Sem" + sem).c_str()));
		fout.open("../Data/School Year/" + year + "/all semester.txt", std::ios::app);			//Open file stored all semester of that year
		fout << x <<"," << StartDate << "," << EndDate << std::endl;														//Write down the semester
		fout.close();
		semester* dummy = new semester(x - '0', StartDate, EndDate);
		if (!(cur->pHeadSemester))
		{
		cur->pHeadSemester = dummy;
			cur->pTailSemester = dummy;
		}
		else
		{
			cur->pTailSemester->pNext = dummy;
			cur->pTailSemester = dummy;
		}
		std::cout << "Create succesfully\n";
		std::cout << "Do you want to add more semester :(Y/N || y/n) ";
		char choice; std::cin >> choice;
		std::cin.ignore();
		if (choice == 'N' || choice == 'n')
			return;
	}
}
void schoolYear::loadFile(std::string year)
{
	fin.open("../Data/School Year/" + year + "/all semester.txt", std::ios::in);
	while (!fin.eof())
	{
		std::string sem,startDate, endDate, redundant;
		getline(fin, redundant);
		if (redundant == "")
		break;
		getline(fin, sem, ',');
		getline(fin, startDate, ',');
		getline(fin, endDate, '\n');
		semester* dummy = new semester(stoi(sem), startDate, endDate);
		if (!pHeadSemester)
		{
			pHeadSemester = dummy;
			pTailSemester = dummy;
		}
		else
		{
			pTailSemester->pNext = dummy;
			pTailSemester = dummy;
		}
	}
	fin.close();
}
bool schoolYear::checkExistSemester(int sem)
{
	for (semester* cur = pHeadSemester; cur; cur = cur->pNext)
	{
		if (sem == cur->getSem())
			return 1;
	}
	return 0;
}
int semester::getSem()
{
	return sem;
}
schoolYear* schoolYear::findSchoolYear(std::string year)
{
	schoolYear* cur = pHeadSchoolYear;
	for (; cur; cur = cur->pNext)
	{
		std::string tmp = cur->getYear();
		if (!tmp.compare(year))
		{
			return cur;
		}
	}
	return nullptr;
}
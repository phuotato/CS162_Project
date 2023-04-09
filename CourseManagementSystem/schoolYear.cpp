#pragma once
#include "SchoolYear.h"
#include "Universal.h"
#include "Graphic.h"
std::ifstream fin;
std::ofstream fout;

//Initialize extern variables
extern schoolYear* curSchoolYear;
extern schoolYear* pHeadSchoolYear;
extern schoolYear* pTailSchoolYear;

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
		gotoxy(12, 0);
		std::cout << "All the year list:\n";
		showSchoolYear();
		std::cout << "Enter your school year you want to create(format:yyyy-yyyy) (Press enter to stop): ";
		std::string year; getline(std::cin, year);

		//checking condition
		if (year == "") break;
		if (checkCorrectYear(year) == false) {
			std::cout << "Please enter the correct year!\n";
			system("pause");
			system("cls");
			continue;
		}

		if (checkExistSchoolYear(year)!=0)
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
			std::cout << "Create succesfully\n";
			std::cout << "Do you want to add more school year:(Y/N || y/n) ";
			char choice; std::cin >> choice;
			std::cin.ignore();
			if (choice == 'N' || choice == 'n')
				return;
		}
		system("pause");
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
			return;
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
		pHeadSchoolYear->pHeadClass->deleteClass();
		schoolYear* tmp = pHeadSchoolYear->pNext;
		delete pHeadSchoolYear;
		pHeadSchoolYear = tmp;

	}
}


//Show SchoolYear

void schoolYear::showSchoolYear()
{
	for (schoolYear* cur = pHeadSchoolYear; cur; cur = cur->pNext)
		std::cout << "\t\t" << cur->getYear() << std::endl;
}


//Create&Information Class

//Constructor for Class
Class::Class(std::string Name) :Name(Name) {}

//Functions for Class
void schoolYear::addNewClass() {
	bool flag = 0;
	while (true) {
		std::cout << "Please enter the name of the class you want to create: ";
		std::cin.ignore();
		std::string Name;  std::cin >> Name;

		if (checkExistClass(Name)) {
			std::cout << "This class is already exist.\n";
			flag = 0;
		}

		else {
			if (!pHeadClass) pHeadClass = new Class("");
			pTailClass = pHeadClass;
			Class* tmp = pTailClass->pNext;

			tmp = new Class(Name);
			pTailClass = tmp->pNext;
			if (pHeadClass->getName() == "") {
				delete pHeadClass;
				pHeadClass = tmp;
			}
			flag = 1;
		}

		if (flag == 1)
		{
			std::cout << "Create succesfully\n";
			std::cout << "Do you want to add more school year:(Y/N || y/n) ";
			char choice; std::cin >> choice;
			std::cin.ignore();
			if (choice == 'N' || choice == 'n')
				return;
		}
	}
}

void schoolYear::createInformationClass() {
	for (schoolYear* cur = pHeadSchoolYear; cur; cur = cur->pNext) {
		std::string year = cur->getYear();											//Find the year to add

		while (true) {
			fin.open(".. /Data/School Year/" + year + "/Class.txt");
			if (!fin.eof()) return;
			std::string ClassName;													//Read in class
			getline(fin, ClassName, ' ');
			if (ClassName == ".") break;
			fin.ignore();

			if (!pHeadClass) pHeadClass = new Class("");
			Class* tmp = pHeadClass;
			tmp->pNext = new Class(ClassName);

			pTailClass = tmp;
			if (pHeadClass->getName() == "") delete pHeadClass;

			fin.close();
		}

	}

}

bool schoolYear::checkExistClass(std::string Name)
{
	if (pHeadClass)
	{
		for (Class* cur = pHeadClass; cur; cur = cur->pNext)
		{
			if (cur->getName() == Name)
				return 0;
		}
	}
	return 1;
}

void Class::deleteClass() {
	for (; pHeadSchoolYear->pHeadClass;)
	{
		Class* tmp = pHeadSchoolYear->pHeadClass;
		delete pHeadSchoolYear->pHeadClass;
		pHeadSchoolYear->pHeadClass = tmp;

	}
}

//Other functions
std::string Class::getName() {
	return Name;
}

std::string schoolYear::getYear()
{
	return year;
}
void schoolYear::createSemester()
{
	char x;
	bool flag = 0;
	std::cout << "Enter school year include your semester:";
	std::string year;
	getline(std::cin, year);
	loadFile(year);
	while(flag)
	for (schoolYear* cur = pHeadSchoolYear; cur; cur = cur->pNext)
	{
		std::string tmp = cur->getYear();
		if (!tmp.compare(year))
		{
			flag = 1;
			break;
		}
	}
	if (flag)
	{
		std::cout << "What is semester you want to create: ";
		while(true)
		{
			std::cout << "Sem:";
			std::cin >> x;
			if ('x' < 1 || x > '3')
			{
				std::cout << "Invalid semester. Try other ones\n";
				continue;
			}
			if (checkExistSemester(x - '0'))
			{
				std::cout << "This semester was already created. Try other ones\n";
				continue;
			}
		}
		fout.open("../Data/School Year/" + year + "/all semester.txt", std::ios::app);			//Open file stored all semester of that year
		fout << "Semester" << " " << x;														//Write down the semester
		fout.close();
		std::cout << "Enter the start date:";
		std::string StartDate;
		getline(std::cin, StartDate);
	}
}
void schoolYear::loadFile(std::string year)
{
	fin.open("../Data/School Year/" + year + "/all semester.txt");
	while (!fin.eof())
	{
		std::string sem, startDate, endDate;
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
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
		showSchoolYear();
		gotoxy(18, 23);
		std::cout << "Would you like to create a new school year? (Y/N): ";
		char option;
		std::cin >> option;

		if (option == 'Y' || option == 'y')
		{
			std::cout << "\t\tEnter new school year (e.g. 2022-2023): ";
			std::string year; getline(std::cin, year);

			//checking condition
			if (checkCorrectYear(year) == false) {
				std::cout << "\t\tPlease enter the correct year!\n";
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
				std::cout << "\t\tThis school year is already created, please enter another school year\n";
				flag = 0;
			}
			if (flag == 1)
			{
				gotoxy(23, 27);
				std::cout << "Created succesfully\n";
				std::cout << "\t\tDo you want to add more school year:(Y/N) ";
				char choice; std::cin >> choice;
				std::cin.ignore();
				if (choice == 'N' || choice == 'n')
					return;
			}
		}
		else return;
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
	gotoxy(30, 3);
	std::cout << "Created School Years\n";
	// Draw box to display school years
	drawBox(10, 6, 60, 10);
	int i = 0;
	for (schoolYear* cur = pHeadSchoolYear; cur; cur = cur->pNext)
	{
		gotoxy(35, 9 + i*2);
		std::cout << cur->getYear() << std::endl;
		++i;
	}
		
}


//Create&Information Class

//Constructor for Class
Class::Class(std::string Name) :Name(Name) {}

//Functions for Class

void Class::LoadFile(std::string curYear)
{
	fin.open("../Data/School Year/" + curYear + "/Class.txt");
	while (!fin.eof())
	{
		std::string curName;
		getline(fin, curName);
		if (curName == "")															//Check if the file is empty or not
			return;
		schoolYear* CurYear = pHeadSchoolYear;
		for (; CurYear; CurYear = CurYear->pNext) {
			if (CurYear->getYear() == curYear) break;
		}

		if (!CurYear->pHeadClass)
		{
			CurYear->pHeadClass = new Class(curName);
			CurYear->pTailClass = CurYear->pHeadClass;
		}
		else
		{
			Class* tmp = new Class(curName);
			CurYear->pTailClass->pNext = tmp;
			CurYear->pTailClass = tmp;
		}
	}
}

void schoolYear::addNewClass() {
	bool flag = 0;
	while (true) {
		//Enter the schoolYear to add
		std::cout << "Please enter the school year you want to add: ";
		std::string Year; std::cin >> Year;
		std::cin.ignore();

		//Find the schoolYear
		fin.open("../Data/School Year/all school year.txt");
		std::string curYear;
		while (!fin.eof())
		{
			getline(fin, curYear);
			if (curYear == "")																		//Check if the file is empty or not
				return;
			if (curYear == Year) {
				flag = 1;
				return;
			}
		}

		if (flag != 1) {
			std::cout << "There is no school year similar to what you input.\n";
			std::cout << "Consider to add new school year.\n";
			return;
		}
		flag = 0;
		fin.close();

		//Enter the class code
		std::cout << "Please enter the name of the class you want to create: ";
		std::string Name;  std::cin >> Name;
		std::cin.ignore();

		//Check the class
		pHeadClass->LoadFile(Year);
		if (checkExistClass(Name)) {
			std::cout << "This class is already exist.\n";
			flag = 0;
		}

		else {
			//Create dummy node and initialize
			if (!pHeadClass) pHeadClass = new Class("");
			pTailClass = pHeadClass;
			Class* tmp = pTailClass;

			//Add the new class
			tmp->pNext = new Class(Name);
			pTailClass = tmp->pNext;
			pTailClass->getName() = Name;
			pTailClass->pNext = nullptr;

			//Delete dummy node
			if (pHeadClass->getName() == "") {
				delete pHeadClass;
				pHeadClass = tmp;
			}

			//Add Class into the text file
			fout.open("../Data/School Year/" + curYear + "/Class.txt", std::ios::app);
			fout << Name;
			fout.close();
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
			if (!fin) return;
			std::string ClassName;													//Read in class
			getline(fin, ClassName, ' ');
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

void Class::Choices() {
	system("cls");
	int k;
	do {
		std::cout << "\n\t\t+--------------------------------------------------+";
		std::cout << "\n\t\t|              MENU OPTIONS                        |";
		std::cout << "\n\t\t+--------------------------------------------------+";
		std::cout << "\n\t\t| 1. Load all classes in all school year           |";
		std::cout << "\n\t\t| 2. Add more class                                |";
		std::cout << "\n\t\t| 0. Exit                                          |";
		std::cout << "\n\t\t+--------------------------------------------------+";
		std::cout << "\n\t\t Enter your choice: ";
		std::cin >> k;
		switch (k) {
			case 1:
				pHeadSchoolYear->createInformationClass();
				break;
			case 2:
				pHeadSchoolYear->addNewClass();
				break;
			default:
				std::cout << "You have entered wrong! Try again.\n";
				break;
		}
		Sleep(1000);
		system("cls");
	}
	while (k != 0);
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
	schoolYear* cur;
	loadFile(year);
	while (true)
	{
		std::cout << "Enter school year include your semester:";
		std::string year;
		getline(std::cin, year);
		if (checkCorrectYear(year))
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
	}
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
		std::cout << "Enter the end date";
		std::string EndDate;
		getline(std::cin, EndDate);
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
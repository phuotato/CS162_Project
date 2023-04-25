#pragma once
#include "SchoolYear.h"
#include "Universal.h"
#include "Graphic.h"
#include "Class.h"
#include "Display.h"

std::ifstream fin;
std::ofstream fout;

//Initialize extern variables
extern schoolYear* curSchoolYear;
extern schoolYear* pHeadSchoolYear;
extern schoolYear* pTailSchoolYear;
extern semester* curSemester;
extern Class* pHeadClass;
extern Class* pTailClass;
extern Class* curClass;
extern int mid;

//Constructor for SchoolYear
schoolYear::schoolYear(std::string time, schoolYear* pointer) :year(time), pNext(pointer) {}
schoolYear::schoolYear() {}

//Create SchoolYear

void schoolYear::createSchoolYear(short& k)
{
	std::cin.ignore(); //remove enter
	loadFile();
	bool flag = 1;
	while (true)
	{
		system("cls");
		drawTutorial(15, 2, 30, 23);
		Tutorial();
		showSchoolYear();
		
		std::cout << "\n"; gotox(mid - 41 / 2);
		std::cout << "Enter new school year (e.g. 2022-2023): ";

		std::cout << "\n"; gotox(mid - 41 / 2);
		std::cout << "Or press enter to go back:";
		std::string year; getline(std::cin, year);

		//if enter then return
		if (year == "") return;

		//checking condition
		if (checkCorrectYear(year) == false) {
			SetColor(7, 12);
			std::cout << "\n\n"; gotox(mid - 29/2);
			std::cout << "Please enter the valid year!";
			SetColor(7, 0);

			Sleep(2000);
			system("cls");
			continue;
		}

		if (checkExistSchoolYear(year) != 0)
		{	
			//Check this is the newest year
			if (year < pTailSchoolYear->getYear()) {
				SetColor(7, 12);
				std::cout << "\n\n"; gotox(mid - 67 / 2);
				std::cout << "This year is not the newest one. Please enter the correct one!";
				SetColor(7, 0);

				Sleep(2000);
				continue;
			}
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
			SetColor(7, 12);
			std::cout << "\n\n\tThis school year is already created, please enter another school year\n";
			SetColor(7, 0);

			Sleep(2000);
			flag = 0;
		}
		if (flag == 1)
		{
			SetColor(7, 2);
			std::cout << "Created succesfully\n";
			SetColor(7, 0);
			k = 0;

			system("pause");
			return;
		}
	}
	
}

//load all schoolyear

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

//check if exist

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

//Make sure a valid schoolyear

bool schoolYear::checkCorrectYear(std::string year) {
	int length = year.length();

	//Check length
	if (length != 9) return false;

	//0->3, 5->8 is number
	for (int i = 0; i < 4; i++) {
		if (year[i] < '0' || year[i] > '9' || year[i + 5] > '9' || year[i + 5] < '0') return false;
	}

	//4-> '-'
	if (year[4] != '-') return false;

	//are two years consecutive
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
	gotoxy(mid-20/2, 3); std::cout << "School Years' List";
	gotoxy(mid - 46 / 2, 4);  std::cout << "+-------------------------------------------+";

	short i = 5;
	for (schoolYear* cur = pHeadSchoolYear; cur; cur = cur->pNext, i++)
	{
		gotoxy(mid - 47 / 2, i); std::cout << "|                 " << cur->getYear() << "                 |";
	}

	gotoxy(mid - 47 / 2, i); std::cout << "+-------------------------------------------+";
	i++;
}

//Choose schoolYear
void schoolYear::chooseSchoolYear(short& k) {
	std::string year;

	system("cls");
	std::cin.ignore(); //Remove enter

	loadFile();
	while (true) {
		drawTutorial(15, 2, 30, 23);
		Tutorial();
		showSchoolYear();

		std::cout << "\n"; gotox(mid - 58 / 2);
		std::cout << "Please choose your school year (Press enter to go back): ";
		getline(std::cin, year);

		if (year == "") return;

		for (schoolYear* cur = pHeadSchoolYear; cur; cur = cur->pNext) {
			if (year == cur->getYear()) {
				SetColor(7, 2);
				std::cout << "\n\n"; gotox(mid - 18 / 2);
				std::cout << "Found! Getting in";
				SetColor(7, 0);

				Sleep(2000);
				curSchoolYear = cur;
				k = 0;
				return;
			}
		}

		//False - warning
		SetColor(7, 12);
		std::cout << "\n\n"; gotox(mid - 24 / 2);
		std::cout << "Please input correctly!";
		SetColor(7, 0);

		//Clear everything to show back
		Sleep(2000);
		system("cls");
		
	}
}

//Other functions

std::string schoolYear::getYear()
{
	return year;
}
bool schoolYear::createSemester()
{
	char x;
	if(!pHeadSemester)
	curSchoolYear->loadFile(year);
	if (!curSchoolYear->checkAvaiSemester())
	{
		gotoxy(17, 15);
		std::cout << "This school year is full of semester";
		std::cout << "\n\t\t Press any key to back:";
		_getch();
		return 0;
	}
	while (true)
	{
		std::cout << "What is semester you want to create: ";
		while (true)
		{
			std::cout << "Sem:";
			std::cin >> x;
			if (x < '1' || x > '3')
			{
				std::cout << "Invalid semester. Try other ones\n";
				continue;
			}
			if (curSchoolYear->checkExistSemester(x - '0'))
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
		// Check length string > 10 return
		// Check string[2] && string[5] == '/'
		// convert int day -> Date.day
		// convert int month -> Date.month
		// convert int year -> Date.year
		// Check day, month year
		// Check string[0] [1] [3] [4] [6] [7] [8] [9] number;
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
		fout << x <<"," << StartDate << "," << EndDate << std::endl;							//Write down the semester
		fout.close();
		semester* dummy = new semester(x - '0', StartDate, EndDate);
		curSchoolYear->increaseSem();
		if (!(curSchoolYear->pHeadSemester))
		{
			curSchoolYear->pHeadSemester = dummy;
			curSchoolYear->pTailSemester = dummy;
		}
		else
		{
			curSchoolYear->pTailSemester->pNext = dummy;
			curSchoolYear->pTailSemester = dummy;
		}
		std::cout << "Create succesfully\n";
		std::cout << "Do you want to add more semester :(Y/N || y/n) ";
		char choice; std::cin >> choice;
		std::cin.ignore();
		if (choice == 'N' || choice == 'n')
			return 1;
		if (!curSchoolYear->checkAvaiSemester())
		{
			std::cout << "This school year is full of semester\n";
			std::cout << "Press any key to back:";
			_getch();
			return 1;
		}
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
			++numSem;
		}
		else
		{
			pTailSemester->pNext = dummy;
			pTailSemester = dummy;
			++numSem;
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

void schoolYear::increaseSem()
{
	++numSem;
}
bool schoolYear::checkAvaiSemester()
{
	if (numSem == 3)
		return 0;
	return 1;
}
bool schoolYear::showSemester()
{
	if(!pHeadSemester)			//load semester
		curSchoolYear->loadFile(year);

	if (!pHeadSemester)			//check pHeadSemester null or not
	{
		std::cout << "This schoolyear haven't had any semester before\n";
		system("pause");
		return 0;
	}
	std::cin.ignore();
	while (true)
	{
		system("cls");
		gotoxy(29, 3);				//show all semester in schoolyear
		std::cout << "Semester's list\n";
		std::cout << "\n\t\t+--------------------------------------+";
		for (semester* cur = pHeadSemester; cur; cur = cur->pNext)
		{
			std::cout << "\n\t\t|                Sem " << cur->getSem() << "                 |";
		}
		std::cout << "\n\t\t+--------------------------------------+";
		std::cout << "\n\t\tPlease choose your semester (Press enter to go back): ";
		std::string sem;
		getline(std::cin, sem);
		if (sem == "") return 0;

		for (semester* cur = pHeadSemester; cur; cur = cur->pNext) {
			if (stoi(sem) == cur->getSem()) {
				SetColor(7, 2);
				std::cout << "\n\n\t\t              Found! Getting in";
				SetColor(7, 0);

				Sleep(2000);
				curSemester = cur;
				return 1;
			}
		}

		//False - warning
		SetColor(7, 12);
		std::cout << "\n\n\t\t          Please input correctly!";
		SetColor(7, 0);

		//Clear everything to show back
		Sleep(2000);
		system("cls");
	}
}
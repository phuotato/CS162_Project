#pragma once
#include "SchoolYear.h"
#include "Universal.h"
#include "Graphic.h"
#include "Class.h"
#include "Display.h"

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
	loadFile();
	std::ofstream fout;
	while (true)
	{
		ShowingList();

		std::cout << "\n"; gotox(mid - 41 / 2);
		std::cout << "Enter new school year (e.g. 2022-2023): \r";

		std::cout << "\n"; gotox(mid - 41 / 2);
		std::cout << "Or press enter to go back:";
		std::string year; getline(std::cin, year);

		if (year.empty())
			return;

		if (!checkCorrectYear(year)) {
			SetColor(7, 12);
			std::cout << "\n\n"; gotox(mid - 29 / 2);
			std::cout << "Please enter a valid year!";
			SetColor(7, 0);

			Sleep(2000);
			system("cls");
			continue;
		}

		if (checkExistSchoolYear(year) != 0)
		{
			if (year < pTailSchoolYear->getYear()) {
				SetColor(7, 12);
				std::cout << "\n\n"; gotox(mid - 50 / 2);
				std::cout << "This year is not the newest one. Please enter the correct one!";
				SetColor(7, 0);

				Sleep(2000);
				continue;
			}

			fout.open("../Data/SchoolYear/all school year.txt", std::ios::app);
			fout << std::endl;
			fout << year;
			fout.close();

			if (_mkdir(("../Data/SchoolYear/" + year).c_str()) == 0) {
				fout.open("../Data/SchoolYear/" + year + "/all semester.txt", std::ios::app);
				fout.close();

				schoolYear* tmp = new schoolYear(year, nullptr);
				if (!pHeadSchoolYear) {
					pHeadSchoolYear = tmp;
					pTailSchoolYear = tmp;
				}
				else {
					pTailSchoolYear->pNext = tmp;
					pTailSchoolYear = tmp;
				}

				SetColor(7, 2);
				std::cout << "\n\n"; gotox(mid - 20 / 2);
				std::cout << "Created successfully\n";
				SetColor(7, 0);
				k = 0;

				loadingPage();
				return;
			}
		}
		else
		{
			SetColor(7, 12);
			std::cout << "\n\n"; gotox(mid - 50 / 2);
			std::cout << "This school year has already been created. Please enter another school year.";
			SetColor(7, 0);

			Sleep(2000);
		}
	}
}

//load all schoolyear

void schoolYear::loadFile()
{
	if (pHeadSchoolYear) return;	//if there is a LL, dont load
	std::ifstream fin;
	fin.open("../Data/SchoolYear/all school year.txt");
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
	curSchoolYear = pHeadSchoolYear;
	fin.close();
}

//check if exist

bool schoolYear::checkExistSchoolYear(const std::string& year)
{
	if (pHeadSchoolYear)
	{
		for (schoolYear* cur = pHeadSchoolYear; cur; cur = cur->pNext)
		{
			if (cur->getYear() == year)
				return false;
		}
	}
	return true;
}

//Make sure a valid schoolyear
bool schoolYear::checkCorrectYear(const std::string& year)
{
	int length = year.length();

	// Check length
	if (length != 9)
		return false;

	// Check year format
	for (int i = 0; i < 4; i++)
	{
		if (!isdigit(year[i]) || !isdigit(year[i + 5]))
			return false;
	}

	// Check delimiter
	if (year[4] != '-')
		return false;

	// Check consecutive years
	int startYear = std::stoi(year.substr(0, 4));
	int endYear = std::stoi(year.substr(5, 4));
	if (endYear - startYear != 1)
		return false;

	return true;
}

//Delete SchoolYear
void schoolYear::deleteSchoolYear()
{
	while (pHeadSchoolYear)
	{
		schoolYear* tmp = pHeadSchoolYear;
		pHeadSchoolYear = pHeadSchoolYear->pNext;
		delete tmp;
	}
	pTailSchoolYear = nullptr; // Reset the tail pointer
}

//Show SchoolYear
void schoolYear::showSchoolYearAll(short range, short& Pcur)
{
	gotoxy(mid-19/2, 3); std::cout << "School Years' List";

	short i = 5;
	short k = 0;
	for (; curSchoolYear && k < range; curSchoolYear = curSchoolYear->pNext, i++, k++)
	{
		gotoxy(mid - 10 / 2, i); std::cout <<curSchoolYear->getYear();
		Pcur++;
	}
	drawBox(mid - 46 / 2, 4, 46, k + 4);
	gotoy(-2);
	drawLine(46, mid - 46 / 2);
	std::cout << "\n\n"; gotox(mid - 46 / 2);
}

void schoolYear::showP(short range, short& Pcur)
{
	curSchoolYear = pHeadSchoolYear;

	//Check if the last page
	if (Pcur % range == 0) {
		for (int i = 0; i < Pcur - range * 2; i++) curSchoolYear = curSchoolYear->pNext;
		Pcur -= range * 2;
	}
	else {
		for (int i = 0; i < Pcur - (Pcur % range) - range; i++) curSchoolYear = curSchoolYear->pNext;
		Pcur -= (Pcur % range) + range;
	}
}

//Choose schoolYear
void schoolYear::chooseSchoolYear(short& k) {
	std::string year;

	system("cls");

	loadFile();
	while (true) {
		//Display Pages
		ShowingList();

		std::cout << "\n"; gotox(mid - 58 / 2);
		std::cout << "Please choose your school year (Press enter to go back): ";
		getline(std::cin, year);

		if (year == "") return;

		for (schoolYear* cur = pHeadSchoolYear; cur; cur = cur->pNext) {
			if (year == cur->getYear()) {
				SetColor(7, 2);
				std::cout << "\n\n"; gotox(mid - 11 / 2);
				std::cout << "Getting in";
				SetColor(7, 0);

				Sleep(250);
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
		Sleep(250);
		system("cls");
		
	}
}

//Get All schoolYear currently
int schoolYear::getAllSchoolYear() {
	int i = 0;
	for (schoolYear* cur = pHeadSchoolYear; cur; cur = cur->pNext, i++);
	return --i;
}

//Function mainly to show
void schoolYear::ShowingList() {
	std::string displayk = "N";
	std::string* content = nullptr;
	bool EnterConfirm = 0;
	int yp = 6;
	short TH = 3;
	short range = 5;
	short Pcur = 0;
	int APages = getAllSchoolYear() / range + 1;
	curSchoolYear = pHeadSchoolYear;

	system("cls");
	while (true) {

		switch (TH) {
			//Next page
			case 3: {
				if (curSchoolYear == nullptr) {
					SetColor(7, 12);
					if (Pcur % range == 0 && Pcur != 0) gotoxy(mid - 25/2,range + 8);
					else gotoxy(mid-25/2,Pcur % range + 8);
					std::cout << "You are at the last page";
					SetColor(7, 0);

					Sleep(1000);

					//Reset the command
					gotox(mid - 47 / 2);
					std::cout << "                                                          \r";

				}
				else {
					system("cls");
					drawBox(15, 2, 30, 23);
					Tutorial(content);
					showSchoolYearAll(range, Pcur);
					Description(range, APages, (Pcur - 1) / range + 1, Pcur, mid - 45 / 2, 46);
				}
				yp = 6;
				break;
			}
			//Previous Page
			case 2: {
				if (Pcur <= range) {
					SetColor(7, 12);
					if (Pcur % range == 0 && Pcur != 0) gotoxy(mid - 25 / 2, range + 8);
					else gotoxy(mid - 25 / 2, Pcur % range + 8);
					std::cout << "You are at the first page";
					SetColor(7, 0);

					Sleep(2000);

					//Reset the command
					gotox(mid - 47 / 2);
					std::cout << "                                                          \r";
					
				}
				else {
					system("cls");
					drawBox(15, 2, 30, 23);
					Tutorial(content);
					showP(range, Pcur);
					showSchoolYearAll(range, Pcur);
					Description(range, APages, (Pcur - 1) / range + 1, Pcur, mid - 45 / 2, 46);
				}
				yp = 6 + 4;
				break;
			}
			//Enter to confirm
			case 0: {
				EnterConfirm = 1;
				break;
			}
			//Change list
			case 1: {

				if (Pcur % range == 0 && Pcur != 0) gotoxy(mid - 50 / 2, range + 8);
				else gotoxy(mid - 50 / 2, Pcur % range + 8);
				std::cout << "Please enter the number you want to change list: ";
				getline(std::cin, displayk);

				if (displayk[0] <= '9' && displayk[0] >= '0') {
					int sample = stoi(displayk);
					if (sample > 10 || sample < 5) {
						SetColor(7, 12);
						std::cout << "\n\n"; gotox(mid - 42 / 2);
						std::cout << "The range is too big or too small (5~10)!";
						SetColor(7, 0);

						Sleep(2000);

						//Reset the command
						gotox(mid - 47 / 2);
						std::cout << "                                                          \r";
						gotoxy(mid - 50 / 2, -3); std::cout << "                                                    ";
					}
					else {
						//Reset everything
						range = sample;
						Pcur = 0;
						curSchoolYear = pHeadSchoolYear;
						APages = getAllSchoolYear() / range + 1;

						//Draw again
						system("cls");
						drawBox(15, 2, 30, 23);
						Tutorial(content);
						showSchoolYearAll(range, Pcur);
						Description(range, APages, (Pcur - 1) / range + 1, Pcur, mid - 45 / 2, 46);
					}
				}
				yp = 6 + 8;
				break;
			}
		}
		if (EnterConfirm == 1) {
			if (Pcur % range == 0 && Pcur != 0) gotoy(range + 8);
			else gotoy(Pcur % range + 8);
			break;
		}
		TH = movingBarTutorial(16, 6, yp, 44, 18, 4, content);
	}
}

//Other functions

std::string schoolYear::getYear()
{
	return year;
}

bool schoolYear::createSemester()
{
	std::ofstream fout;
	char x;
	if(!pHeadSemester)
	curSchoolYear->loadFileSemester(year);
	if (!curSchoolYear->checkAvaiSemester())
	{
		gotoxy(mid - 37 / 2, 18);
		SetColor(7, 4);
		std::cout << "This school year is full of semester\n";
		SetColor(7, 0);

		gotox(mid - 23/2);
		std::cout << "Press any key to go back...";
		_getch();
		return 0;
	}
	while (true)
	{
		gotoxy(mid - 61 / 2, 17);
		std::cout << "What is semester you want to create: ";
		while (true)
		{
			gotoxy(mid - 61 / 2,18); std::cout << "                          ";
			gotoxy(mid - 61 / 2,18); std::cout << "Sem:";
			std::cin >> x;
			if (x < '1' || x > '3')
			{
				SetColor(7, 4);
				std::cout << "\n"; gotox(mid - 34 / 2);
				std::cout << "Invalid semester. Try other ones";
				SetColor(7, 0);
				Sleep(1000);

				//Reset
				gotox(mid - 34 / 2); std::cout << "                                 ";
				gotoy(-2);
				continue;
			}
			if (curSchoolYear->checkExistSemester(x - '0'))
			{
				SetColor(7, 4);
				std::cout << "\n"; gotox(mid - 16 / 2);
				std::cout << "Already created";
				SetColor(7, 0);
				Sleep(1000);

				//Reset
				gotox(mid - 16 / 2); std::cout << "               ";
				gotoy(-2);
				continue;
			}
			break;
		}
		fout.open("../Data/SchoolYear/" + year + "/all semester.txt", std::ios::app);			//Open file stored all semester of that year
		fout << "Semester " << x << std::endl;														//Write down the semester
		fout.close();

		gotox(mid - 61 / 2); std::cout << "Enter the start date: ";
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

		gotox(mid - 61 / 2); std::cout << "Enter the end date: ";
		std::string EndDate;
		getline(std::cin, EndDate);

		std::string sem;
		sem += x;
		if (_mkdir(("../Data/SchoolYear/" + year + "/Sem" + sem).c_str()));
		fout.open("../Data/SchoolYear/" + year + "/all semester.txt", std::ios::app);			//Open file stored all semester of that year
		fout << x << "," << StartDate << "," << EndDate << std::endl;							//Write down the semester
		fout.close();

		semester* dummy = new semester(x - '0', StartDate, EndDate);
		curSchoolYear->increaseSem();
		if (!(curSchoolYear->pHeadSemester))
		{
			curSchoolYear->pHeadSemester = dummy;
			curSchoolYear->pTailSemester = dummy;
			curSemester = dummy;
		}
		else
		{
			curSchoolYear->pTailSemester->pNext = dummy;
			curSchoolYear->pTailSemester = dummy;
			curSemester = dummy;
		}
		std::cout << "\n\n"; gotox(mid - 48 / 2);
		loadingPage();
		gotox(mid - 27 / 2); std::cout << "                                                               ";
		gotoxy(mid - 10 / 2, -2); std::cout << "                                                          ";
		SetColor(7, 2);
		gotox(mid - 20 / 2);
		std::cout << "Created Succesfully";
		SetColor(7, 0);
		Sleep(1000);
		return 1;
	}
}
void schoolYear::loadFileSemester(std::string year)
{
	std::ifstream fin;
	fin.open("../Data/SchoolYear/" + year + "/all semester.txt", std::ios::in);
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
			return true;
	}
	return false;
}
int semester::getSem()
{
	return sem;
}

schoolYear* schoolYear::findSchoolYear(const std::string& year)
{
	for (schoolYear* cur = pHeadSchoolYear; cur; cur = cur->pNext)
	{
		if (cur->getYear() == year)
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
		return false;
	return true;
}

bool schoolYear::showSemester()
{
	if (!pHeadSemester)			//load semester
		loadFileSemester(year);

	if (!pHeadSemester)			//check pHeadSemester null or not
	{
		std::cout << "\n";
		gotox(mid - 48 / 2);
		SetColor(7, 4);
		std::cout << "This school year hasn't had any semester before\n\n";
		SetColor(7, 0);
		gotox(mid - 28 / 2);
		system("pause");
		return false;
	}

	while (true)
	{
		system("cls");

		//show all semester in schoolyear
		drawHeader();
		std::cout << "\n\n";
		gotox(mid - 17 / 2); SetColor(7, 9); 
		std::cout << "Semester's list\n\n"; 
		SetColor(7, 0);

		short k = 0;
		for (semester* cur = pHeadSemester; cur; cur = cur->pNext)
		{
			gotox(mid - 6 / 2); std::cout << "Sem " << cur->getSem() << "\n";
			k++;
		}
		drawBox(mid - 53 / 2, 9, 53, 2 + k);
		std::cout << "\n"; gotox(mid - 55 / 2);
		std::cout << "Please choose your semester (Press enter to go back): ";
		std::string sem;
		getline(std::cin, sem);
		if (sem.empty())
			return false;

		for (semester* cur = pHeadSemester; cur; cur = cur->pNext) {
			if (stoi(sem) == cur->getSem()) {
				SetColor(7, 2); std::cout << "\n\n";
				gotox(mid - 18/2); std::cout << "Found! Getting in";
				SetColor(7, 0);

				Sleep(500);
				curSemester = cur;
				return 1;
			}
		}

		//False - warning
		SetColor(7, 12); std::cout << "\n\n";
		gotox(mid - 24 / 2); std::cout << "Please input correctly!";
		SetColor(7, 0);

		//Clear everything to show again
		Sleep(500);
		system("cls");
	}
}

void schoolYear::deleteSemesterList()
{
	for (schoolYear* cur = pHeadSchoolYear; cur; cur = cur->pNext)
	{
		for (semester* tmp = cur->pHeadSemester; tmp;)
		{
			semester* dummy = tmp->pNext;
			delete tmp;
			tmp = dummy;
		}
	}
}
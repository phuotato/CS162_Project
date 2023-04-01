#include "Universal.h"
ifstream fin;
ofstream fout;
bool schoolYear::createSemester()
{
	cout << "What is semester you want to create: ";
	int x; cin >> x;
	if (arrSemester[x - 1])
	{
		cout << "This semester is already created. Please try again others.\n";
		return 0;
	}
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
schoolYear::schoolYear(string time, schoolYear* pointer) :year(time), pNext(pointer) {}
schoolYear::schoolYear() {}
date::date(int Month, int Day, int Year) :month(Month), day(Day), year(Year) {}
semester::semester(int Sem, int Day1, int Month1, int Year1, int Day2, int Month2, int Year2)
	:sem(Sem), startDate(Day1, Month1, Year1), endDate(Day2, Month2, Year2) {}
void school::createSchoolYear()
{
	bool flag = 1;
	while (true)
	{
		if (!pHeadSchoolYear)
		{
			cout << "Enter your school year you want to create: ";
			string year; getline(cin, year);
			fout.open("../School Year/all school year.txt", ios::app);
			fout << year;
			fout.close();
			if (_mkdir(("../School Year/" + year).c_str()));
			pHeadSchoolYear = new schoolYear(year, nullptr);
			pTailSchoolYear = pHeadSchoolYear;
		}
		else
		{
			cout << "Enter your school year you want to create: ";
			string year; getline(cin, year);
			if (checkExistSchoolYear(year))
			{
				fout.open("../School Year/all school year.txt", ios::app);
				fout << endl << year;
				fout.close();
				if (_mkdir(("../School Year/" + year).c_str()));
				schoolYear* tmp = new schoolYear(year, nullptr);
				pTailSchoolYear->pNext = tmp;
				pTailSchoolYear = tmp;
				flag = 1;
			}
			else
			{
				cout << "This school year is already created, please enter another school year\n";
				flag = 0;
			}
		}
		if (flag)
		{
			cout << "Create succesfully\n";
			cout << "Do you want to add more school year:(Y/N || y/n) ";
			char choice; cin >> choice;
			cin.ignore();
			if (choice == 'N' || choice == 'n')
				return;
		}
	}
}
string schoolYear::getYear()
{
	return year;
}
void school::createSemesterFromSchoolYear()
{
	bool flag = 1;
	while (true)
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
		{
			cout << "Create semester successfully\n";
			cout << "Do you want to add more semester:(Y/N || y/n) ";
			char choice; cin >> choice;
			cin.ignore();
			if (choice == 'N' || choice == 'n')
				return;
		}
	}
}
void school::deleteSchoolYear()
{
	for (pHeadSchoolYear; pHeadSchoolYear;)
	{
		schoolYear* tmp = pHeadSchoolYear->pNext;
		delete pHeadSchoolYear;
		pHeadSchoolYear = tmp;
	}
}
void school::showSchoolYear()
{
	for (schoolYear* cur = pHeadSchoolYear; cur; cur = cur->pNext)
		cout << cur->getYear() << " ";
}
void school::loadFile()
{
	fin.open("../School Year/all school year.txt");
	while (!fin.eof())
	{
		string year;
		getline(fin, year);
		if (year == "")
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
bool school::checkExistSchoolYear(string year)
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
int semester::getSem()
{
	return sem;
}
date semester::getStartDate()
{
	return startDate;
}
date semester::getEndDate()
{
	return endDate;
}
void schoolYear::showSemester()
{
	for (int i = 0; i < 3; ++i)
	{
		if (arrSemester[i])
		{
			cout << "Sem " << i + 1 << ":\n";
			cout << arrSemester[i]->getSem() << endl;
			arrSemester[i]->getStartDate().getDate();
			cout << endl;
			arrSemester[i]->getEndDate().getDate();
			cout << endl;
		}
	}
}
void date::getDate()
{
	cout << day << " " << month << " " << year;
}
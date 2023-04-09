#include "Universal.h"
ifstream fin;
ofstream fout;

void schoolYear::createSemester(string year)
{
	loadFile(year);
	bool flag = 1;
	while (true)
	{
		if (!pHeadSemester)
		{
			cout << "What is semester you want to create: ";
			string x;
			getline(cin, x);
			fout.open("../School Year/" + year + "/all semester.txt", ios::app);			//Open file stored all semester of that year
			fout << "Semester " + x;														//Write down the semester
			fout.close();

			//Create a new semester and store in linked list
			std::cout << "Enter the start date of the semester:\n";
			std::cout << "Day: "; int day1; cin >> day1;
			std::cout << "Month: "; int month1; cin >> month1;
			std::cout << "Year: "; int year1; cin >> year1;
			std::cout << "Enter the end date of the semester:\n";
			std::cout << "Day: "; int day2; cin >> day2;
			std::cout << "Month: "; int month2; cin >> month2;
			std::cout << "Year: "; int year2; cin >> year2;
			
			//Check folder and write down information for the semester
			if (_mkdir(("../School Year/" + year + "/Semester " + x).c_str()));
			fout.open("../School Year/" + year + "/Semester " + x + "/information.txt");
			fout << day1 << "," << month1 << "," << year1 << "," << day2 << "," << month2 << "," << year2;
			fout.close();

			pHeadSemester = new semester(stoi(x), day1, month1, year1, day2, month2, year2);
			pTailSemester = pHeadSemester;
		}
		else
		{
			std::cout << "What is semester you want to create: ";
			string x;
			getline(cin, x);
			if (checkExistSemester(stoi(x)))
			{
				fout.open("../School Year/" + year + "/all semester.txt", ios::app);		//Open file stored all semester of that year
				fout << endl << "Semester " + x;											//Write down the semester
				fout.close();

				//Create a new semester and store in linked list
				cout << "Enter the start date of the semester:\n";
				cout << "Day: "; int day1; cin >> day1;
				std::cout << "Month: "; int month1; cin >> month1;
				std::cout << "Year: "; int year1; cin >> year1;
				std::cout << "Enter the end date of the semester:\n";
				std::cout << "Day: "; int day2; cin >> day2;
				std::cout << "Month: "; int month2; cin >> month2;
				std::cout << "Year: "; int year2; cin >> year2;

				//Check folder and write down information for the semester
				if (_mkdir(("../School Year/" + year + "/Semester " + x).c_str()));
				fout.open("../School Year/" + year + "/Semester " + x + "/information.txt");
				fout << day1 << "," << month1 << "," << year1 << "," << day2 << "," << month2 << "," << year2;
				fout.close();

				semester* tmp = new semester(stoi(x), day1, month1, year1, day2, month2, year2);
				pTailSemester->pNext = tmp;
				pTailSemester = tmp;
				flag = 1;
			}
			else
			{
				std::cout << "This semester is already created, please enter another semester\n";
				flag = 0;
			}
		}
		if (flag)
		{
			std::cout << "Create succesfully\n";
			std::cout << "Do you want to add more semester on this school year:(Y/N || y/n) ";
			char choice; cin >> choice;
			cin.ignore();
			if (choice == 'N' || choice == 'n')
				return;
		}
	}
}
schoolYear::schoolYear(string time, schoolYear* pointer) :year(time), pNext(pointer) {}
schoolYear::schoolYear() {}

date::date(int Month, int Day, int Year) :month(Month), day(Day), year(Year) {}

semester::semester(int Sem, int Day1, int Month1, int Year1, int Day2, int Month2, int Year2)
	:sem(Sem), startDate(Day1, Month1, Year1), endDate(Day2, Month2, Year2) {}

void school::createSchoolYear()
{
	loadFile();
	bool flag = 1;
	while (true)
	{
		if (!pHeadSchoolYear)
		{
			std::cout << "Enter your school year you want to create: ";
			string year; getline(cin, year);

			//Create a new schoolyear and store in linked list
			fout.open("../School Year/all school year.txt", ios::app);						//Open file stored all year of school
			fout << year;																	//Write down the schoolyear
			fout.close();

			//Check folder and write down information for the schoolyear
			if (_mkdir(("../School Year/" + year).c_str()));
			fout.open("../School Year/" + year + "/all semester.txt", ios::app);
			fout.close();

			pHeadSchoolYear = new schoolYear(year, nullptr);
			pTailSchoolYear = pHeadSchoolYear;
		}
		else
		{
			std::cout << "Enter your school year you want to create: ";
			string year; getline(cin, year);
			if (checkExistSchoolYear(year))
			{
				//Create a new schoolyear and store in linked list
				fout.open("../School Year/all school year.txt", ios::app);					//Open file stored all year of school
				fout << endl << year;														//Write down the schoolyear
				fout.close();

				//Check folder and write down information for the schoolyear
				if (_mkdir(("../School Year/" + year).c_str()));
				fout.open("../School Year/" + year + "/all semester.txt", ios::app);
				fout.close();

				schoolYear* tmp = new schoolYear(year, nullptr);
				pTailSchoolYear->pNext = tmp;
				pTailSchoolYear = tmp;
				flag = 1;
			}
			else
			{
				std::cout << "This school year is already created, please enter another school year\n";
				flag = 0;
			}
		}
		if (flag)
		{
			std::cout << "Create succesfully\n";
			std::cout << "Do you want to add more school year:(Y/N || y/n) ";
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

//Edit while running app - Add more semester
void school::createSemesterFromSchoolYear()
{
	bool flag = 1;
	while (true)
	{
		std::cout << "Enter schoolyear include your create semester: ";
		string year; getline(cin, year);
		schoolYear* cur = pHeadSchoolYear;
		for (; cur; cur = cur->pNext)
		{
			string tmp = cur->getYear();
			if (!tmp.compare(year))
				break;
		}
		cur->createSemester(year);
		std::cout << "Do you want to edit other schoolyear:(Y/N || y/n) ";
		char choice; cin >> choice;
		cin.ignore();
		if (choice == 'N' || choice == 'n')
			return;
	}
}

void school::deleteSchoolYear()
{
	for (pHeadSchoolYear; pHeadSchoolYear;)
	{		
		//delete semester
		for (semester* pHead = pHeadSchoolYear->getSemester(); pHead;) {
				semester* tmp = pHead->pNext;
				delete pHead;
				pHead = tmp;
		}

		//delete schoolYear
		schoolYear* tmp = pHeadSchoolYear->pNext;
		delete pHeadSchoolYear;
		pHeadSchoolYear = tmp;

	}
}
void school::showSchoolYear()
{
	for (schoolYear* cur = pHeadSchoolYear; cur; cur = cur->pNext)
		std::cout << cur->getYear() << " ";
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
void schoolYear::loadFile(string year)
{
	fin.open("../Data/School Year/" + year + "/all semester.txt");
	while (!fin.eof())
	{
		string sem, day1, month1, year1, day2, month2, year2;
		getline(fin, sem, ',');
		getline(fin, day1, ',');
		getline(fin, month1, ',');
		getline(fin, year1, ',');
		getline(fin, day2, ',');
		getline(fin, month2, ',');
		getline(fin, year2, '\n');
		if (!pHeadSemester)
		{
			pHeadSemester = new semester(stoi(sem), stoi(day1), stoi(month1), stoi(year1), stoi(day2), stoi(month2), stoi(year2));
			pTailSemester = pHeadSemester;
		}
		else
		{
			semester* tmp = new semester(stoi(sem), stoi(day1), stoi(month1), stoi(year1), stoi(day2), stoi(month2), stoi(year2));
			pTailSemester->pNext = tmp;
			pTailSemester = tmp;
		}
	}
}
bool schoolYear::checkExistSemester(int sem)
{
	for (semester* cur = pHeadSemester; cur; cur = cur->pNext)
	{
		if (sem == cur->getSem())
			return 0;
	}
	return 1;
}

void semester::getInformation()
{
	cout << sem << "," << startDate.getDay() << "," << startDate.getMonth() << "," << startDate.getYear() << "," << endDate.getDay() << "," << endDate.getMonth() << "," << endDate.getYear() << endl;
}
semester* schoolYear::getSemester() {
	return schoolYear::pHeadSemester;
}

int date::getDay()
{
	return day;
}
int date::getMonth()
{
	return month;
}
int date::getYear()
{
	return year;
}
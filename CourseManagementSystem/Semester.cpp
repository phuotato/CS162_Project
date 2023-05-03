#include "Semester.h"
#include "schoolYear.h"
#include "Universal.h"
#include "Course.h"
#include "Graphic.h"
//Extern variables
extern semester* curSemester;
extern schoolYear* curSchoolYear;
extern course* curCourse;
//std::ifstream fin;
//std::ifstream fout;
semester::semester(int Sem, std::string StartDate, std::string EndDate)
	:sem(Sem), startDate(StartDate), endDate(EndDate) {}
semester::semester() {}

//Function
void semester::addCourse()
{
	std::ofstream fout;
	char choice = 'Y';
	while (choice == 'Y' || choice == 'y')
	{
		std::cin.ignore();
		std::cout << "Enter the name of the course: ";		// get information about the course
		std::string name; getline(std::cin, name, '\n');
		std::cout << "Enter the course's ID: ";
		std::string ID; getline(std::cin, ID);
		std::cout << "Enter the classname: ";
		std::string className; getline(std::cin, className);
		std::cout << "Enter the lecturer of the course: ";
		std::string lecturer; getline(std::cin, lecturer);
		std::cout << "Input the course's credit: ";
		int credit; std::cin >> credit;
		std::cout << "Input the maximum student of this course: ";
		int maxStudent; std::cin >> maxStudent;
		std::cin.ignore();
		std::cout << "Which day will the course be performed? ";
		std::string weekDay; getline(std::cin, weekDay);
		std::cout << "Enter the session that the course will be performed (1: 07:30, 2: 09:30, 3: 13:30, 4: 15:30): ";
		int session; std::cin >> session;
		if (pHeadCourse)
		{
			pTailCourse->pNext= new course(ID, name, className, lecturer, credit, maxStudent, stoi(weekDay), session);
			pTailCourse = pTailCourse->pNext;
		}
		else
		{
			pHeadCourse= new course(ID, name, className, lecturer, credit, maxStudent, stoi(weekDay), session);
			pTailCourse = pHeadCourse;
		}
		// save course ID to textfile
		fout.open("../Data/School Year/" + curSchoolYear->year + "/Sem" + std::to_string(curSemester->getSem()) + "/course.txt", std::ios::app);
		if (!fout.is_open())
			std::cout << "Khong the mo";
		else
			fout << ID << std::endl;
		fout.close();
		std::string sem = std::to_string(curSemester->getSem());
		saveCoursetoFolder(name, ID, className, lecturer, credit, maxStudent, weekDay, session, curSchoolYear->year, sem);// function call
		std::cout << "Would you like to add more courses for this semester? Enter Y (or y) to continue adding or enter N (or n) to stop the process: ";
		std::cin >> choice;
	}
}
void semester::saveCoursetoFolder(std::string& name, std::string& id, std::string& className, std::string& lecturer, int& credit, int& maxStudent, std::string& weekDay, int& session, std::string& year, std::string& semester)
{
	std::ofstream fout;
	if (_mkdir(("../Data/School Year/" + year + "/Sem" + semester + "/" + id).c_str()));	// create course folder
	fout.open("../Data/School Year/" + year + "/Sem" + semester + "/" + id + "/information.txt",std::ios::app);
	if (!fout.is_open())
	{
		std::cout << "Khong the mo";
	}
	else
	{
		fout << id << std::endl;
		fout << name << std::endl;
		fout << className << std::endl;
		fout << lecturer << std::endl;
		fout << credit << std::endl;
		fout << maxStudent << std::endl;
		fout << weekDay << std::endl;
		fout << session;
	}
	fout.close();
}

bool semester::showCourse()
{
	if (!pHeadCourse)
		curSemester->loadCourse();
	if (!pHeadCourse)
	{
		gotoxy(17, 30);
		std::cout << "This semster haven't had any course before";
		std::cout << "\n\t\t Press any to continue:";
		std::cin.get();
		return 0;
	}
	else
	{
		while (true)
		{
			system("cls");
			gotoxy(50, 3);				//show all course in semester
			std::cout << "Courses's list\n";
			std::cout << "\n\t\t+----------------------------------------------------------------------------+";
			int x = 0;
			for (course* cur = pHeadCourse; cur; cur = cur->pNext)
			{
				gotoxy(16, 6 + x); std::cout << "|";
				gotoxy(34, 6 + x); std::cout << cur->name << "(" << cur->id << ")";
				gotoxy(93, 6 + x); std::cout << "|";
				++x;
			}
			std::cout << "\n\t\t+----------------------------------------------------------------------------+";
			std::cout << "\n\t\tPlease choose your course's id (Press enter to go back): ";
			std::string Id;
			getline(std::cin, Id);
			if (Id == "") return 0;
			for (course* cur = pHeadCourse; cur; cur = cur->pNext) {
				if (cur->id == Id) {
					SetColor(7, 2);
					std::cout << "\n\n\t\t              Found! Getting in";
					SetColor(7, 0);

					Sleep(500);
					curCourse = cur;
					return 1;
				}
			}

			//False - warning
			SetColor(7, 12);
			std::cout << "\n\n\t\t          Please input correctly!";
			SetColor(7, 0);

			//Clear everything to show back
			Sleep(500);
			system("cls");
		}
	}
}
void semester::loadCourse()
{
	std::ifstream fin ("../Data/School Year/" + curSchoolYear->year + "/Sem" + std::to_string(curSemester->getSem()) + "/course.txt");
	if (!fin.is_open())
		std::cout << "Khong the mo";
	else
	{
		while(!fin.eof())
		{
			std::string Id;
			getline(fin, Id);
			std::ifstream read("../Data/School Year/" + curSchoolYear->year + "/Sem" + std::to_string(curSemester->getSem()) + "/" + Id + "/information.txt");
			if (!read.is_open())
				std::cout << "Khong the mo";
			else
			{
				std::string redundant,name, className, lecturer;
				int credit, maxStudent, weekDay, session;
				getline(read,redundant);
				getline(read, name);
				getline(read, className);
				getline(read, lecturer);
				read >> credit >> maxStudent >> weekDay >> session;
				if (pHeadCourse)
				{
					pTailCourse->pNext = new course(Id, name, className, lecturer, credit, maxStudent, weekDay, session);
					pTailCourse = pTailCourse->pNext;
				}
				else
				{
					pHeadCourse = new course(Id, name, className, lecturer, credit, maxStudent, weekDay, session);
					pTailCourse = pHeadCourse;
				}
			}
			read.close();
		}
	}
}

void semester::deleteCourse()
{
	if (pHeadCourse == curCourse)
	{
		pHeadCourse = pHeadCourse->pNext;
		if (!pHeadCourse)
			pTailCourse = pHeadCourse;
		delete curCourse;
	}
	for (course* tmp = pHeadCourse; tmp->pNext; )
	{
		if (tmp->pNext == curCourse)
		{
			tmp->pNext = tmp->pNext->pNext;
			if (!tmp->pNext)
				pTailCourse = tmp;
			delete curCourse;
		}

	}
}
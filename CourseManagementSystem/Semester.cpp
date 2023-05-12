#include "Semester.h"
#include "schoolYear.h"
#include "Universal.h"
#include "Course.h"
#include "Graphic.h"
#include "Display.h"

//Extern variables
extern semester* curSemester;
extern schoolYear* curSchoolYear;
extern course* curCourse;
extern int mid;

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
		system("cls");
		//header
		drawHeader();
		std::cout << "\n"; gotox(mid - 16 / 2);
		SetColor(7, 9);
		std::cout << "Create Course\n\n";
		SetColor(7, 0);

		gotox(mid - 49/2);
		std::cout << "Enter the name of the course: ";		// get information about the course
		std::string name; getline(std::cin, name, '\n');

		gotox(mid - 49 / 2);
		std::cout << "Enter the course's ID: ";
		std::string ID; getline(std::cin, ID);

		gotox(mid - 49 / 2);
		std::cout << "Enter the classname: ";
		std::string className; getline(std::cin, className);

		gotox(mid - 49 / 2);
		std::cout << "Enter the lecturer of the course: ";
		std::string lecturer; getline(std::cin, lecturer);

		gotox(mid - 49 / 2);
		std::cout << "Input the course's credit: ";
		int credit; std::cin >> credit;

		gotox(mid - 49 / 2);
		std::cout << "Input the maximum student of this course: ";
		int maxStudent; std::cin >> maxStudent;
		std::cin.ignore();

		gotox(mid - 49 / 2);
		std::cout << "Which day will the course be performed? FRI-SAT ";
		std::string weekDay; getline(std::cin, weekDay);

		gotox(mid - 49 / 2);
		std::cout << "Enter the session that the course will be performed\n";

		gotox(mid - 49 / 2);
		std::cout << "(1: 07 : 30, 2 : 09 : 30, 3 : 13 : 30, 4 : 15 : 30): ";
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
		fout.open("../Data/SchoolYear/" + curSchoolYear->year + "/Sem" + std::to_string(curSemester->getSem()) + "/course.txt", std::ios::app);
		if (!fout.is_open()) {
			std::cout << "\n"; gotox(mid - 21 / 2);
			SetColor(7, 4); std::cout << "Error in saving file"; SetColor(7, 0);
		}
		else fout << ID << std::endl;
		fout.close();
		std::string sem = std::to_string(curSemester->getSem());
		saveCoursetoFolder(name, ID, className, lecturer, credit, maxStudent, weekDay, session, curSchoolYear->year, sem);// function call

		loadingPage();

		std::cout << "\n\n"; gotox(mid - 20 / 2);
		SetColor(7, 2);
		std::cout << " Create succesfully";
		SetColor(7, 0);

		Sleep(500);
		//Reset
		gotox(mid - 20 / 2); std::cout << "                            ";
		gotoxy(mid - 26 / 2, -2); std::cout << "                           ";
		gotoxy(mid - 12 / 2, -2); std::cout << "                           ";

		gotoxy(mid - 49 / 2, -1); std::cout << "Would you like to add more courses for this semester?(Y/N) : ";
		std::cin >> choice;
	}
}
void semester::saveCoursetoFolder(const std::string& name, const std::string& id, const std::string& className, const std::string& lecturer, int credit, int maxStudent, const std::string& weekDay, int session, const std::string& year, const std::string& semester)
{
	std::ofstream fout;
	std::string folderPath = "../Data/SchoolYear/" + year + "/Sem" + semester + "/" + id;

	if (_mkdir(folderPath.c_str()) == 0) // create course folder
	{
		fout.open(folderPath + "/information.txt", std::ios::trunc);
		if (fout.is_open())
		{
			fout << id << '\n';
			fout << name << '\n';
			fout << className << '\n';
			fout << lecturer << '\n';
			fout << credit << '\n';
			fout << maxStudent << '\n';
			fout << weekDay << '\n';
			fout << session;
			fout.close();

			gotox(mid - 49 / 2);
			std::cout << "Course information saved successfully.\n";
		}
		else
		{
			gotox(mid - 49 / 2);
			std::cout << "Unable to open the file for saving course information.\n";
		}
	}
	else
	{
		gotox(mid - 49 / 2);
		std::cout << "Unable to create the course folder.\n";
	}
}


int semester::getAllCourses(course* pHead) {
	int i = 0;
	for (course* cur = pHead; cur; cur = cur->pNext, i++);
	return --i;
}

void semester::showCourses(course*& pHead, short range, short& Pcur) {
	gotoxy(mid - 15 / 2, 3);
	std::cout << "Courses' List";

	short i = 5;
	short k = 0;
	for (; pHead && k < range; pHead = pHead->pNext, i++, k++)
	{
		int lengthn = pHead->name.length();
		int lengthid = pHead->id.length();
		gotoxy(mid - (lengthid+lengthn) / 2, i);  std::cout << pHead->name << "(" << pHead->id << ")\n";
		Pcur++;
	}
	drawBox(mid - 46 / 2, 4, 46, k + 4);
	gotoy(-2);
	drawLine(46, mid - 46 / 2);
	std::cout << "\n\n"; gotox(mid - 46 / 2);
}

void semester::showPCourses(course*& pHead, short range, short& Pcur) {
	//Check if the last page
	if (Pcur % range == 0) {
		for (int i = 0; i < Pcur - range * 2; i++) pHead = pHead->pNext;
		Pcur -= range * 2;
	}
	else {
		for (int i = 0; i < Pcur - (Pcur % range) - range; i++) pHead = pHead->pNext;
		Pcur += -(Pcur % range) - range;
	}
}

void semester::showingCourseList(course* pHead) {
	std::string displayk = "N";
	std::string* content = nullptr;
	bool EnterConfirm = 0;
	int yp = 6;
	short TH = 3;
	short range = 5;
	short Pcur = 0;
	int APages = getAllCourses(pHead) / range + 1;
	course* pTail = pHead;
	course* cur = pHead;
	for (; pTail->pNext; pTail = pTail->pNext);


	system("cls");
	while (true) {

		switch (TH) {
		//Next page
		case 3: {
			if (curSchoolYear == nullptr) {
				SetColor(7, 12);
				if (Pcur % range == 0 && Pcur != 0) gotoxy(mid - 25 / 2, range + 8);
				else gotoxy(mid - 25 / 2, Pcur % range + 8);
				std::cout << "You are at the last page";
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
				showCourses(cur, range, Pcur);
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
				showPCourses(cur, range, Pcur);
				showCourses(cur, range, Pcur);
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
					cur = pHead;
					APages = getAllCourses(cur) / range + 1;

					//Draw again
					system("cls");
					drawBox(15, 2, 30, 23);
					Tutorial(content);
					showCourses(cur, range, Pcur);
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

bool semester::viewCourse()
{
	if (!pHeadCourse)
		curSemester->loadCourse();
	if (!pHeadCourse)
	{
		gotoxy(mid - 43 / 2, 5);
		SetColor(7, 4);
		std::cout << "This semster haven't had any course before\n";
		SetColor(7, 0);
		gotox(mid - 43 / 2); std::cout << "Press any keys to continue:";
		std::cin.get();
		return 0;
	}
	else
	{
		while (true)
		{
			system("cls");
			//show all course in semester
			showingCourseList(pHeadCourse);
			
			int x = 0;

			std::cout << "\n"; gotox(mid - 58 / 2);
			std::cout << "Please choose your course's id (Press enter to go back): ";
			std::string Id;
			getline(std::cin, Id);

			if (Id == "") return 0;

			for (course* cur = pHeadCourse; cur; cur = cur->pNext) {
				if (cur->id == Id) {
					std::cout << "\n"; gotox(mid - 18 / 2);
					SetColor(7, 2);
					std::cout << "Found! Getting in";
					SetColor(7, 0);

					Sleep(500);
					curCourse = cur;
					return 1;
				}
			}

			//False - warning
			std::cout << "\n"; gotox(mid - 24 / 2);
			SetColor(7, 12);
			std::cout << "Please input correctly!";
			SetColor(7, 0);

			//Clear everything to show back
			Sleep(500);
			system("cls");
		}
	}
}
void semester::loadCourse()
{
	std::ifstream fin ("../Data/SchoolYear/" + curSchoolYear->year + "/Sem" + std::to_string(curSemester->getSem()) + "/course.txt");
		while(!fin.eof())
		{
			std::string Id;
			getline(fin, Id);
			std::ifstream read("../Data/SchoolYear/" + curSchoolYear->year + "/Sem" + std::to_string(curSemester->getSem()) + "/" + Id + "/information.txt");
			if(read.is_open())
			{
				std::string redundant, name, className, lecturer;
				int credit, maxStudent, weekDay, session;
				getline(read, redundant);
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

void semester::deleteCourse()
{
	if (pHeadCourse == curCourse)
	{
		pHeadCourse = pHeadCourse->pNext;
		if (!pHeadCourse)
			pTailCourse = pHeadCourse;
		delete curCourse;
	}
	for (course* tmp = pHeadCourse; tmp->pNext; tmp=tmp->pNext)
	{
		if (tmp->pNext == curCourse)
		{
			std::string folderPath = "../Data/SchoolYear/" + curSchoolYear->year + "/Sem" + std::to_string(curSemester->getSem()) + "/" + tmp->pNext->id ;
			std::string fileName = "../Data/SchoolYear/" + curSchoolYear->year + "/Sem" + std::to_string(curSemester->getSem()) + "/" + tmp->pNext->id + "/information.txt";
			const char* c = fileName.c_str();
			remove(c);
			if (_rmdir(folderPath.c_str()) == 0);
			tmp->pNext = tmp->pNext->pNext;
			if (!tmp->pNext)
				pTailCourse = tmp;
			delete curCourse;
			std::ofstream fout("../Data/SchoolYear/" + curSchoolYear->year + "/Sem" + std::to_string(curSemester->getSem()) + "/course.txt", std::ios::trunc);
			if (fout.is_open())
			{
				for (course* tmp = curSemester->pHeadCourse; tmp; tmp = tmp->pNext)
				{
					fout << tmp->id << std::endl;
				}
			}
			break;
		}
	}
	std::cout << "\nDelete successfully\n";
}
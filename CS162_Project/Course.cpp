#include "Universal.h"
#include <fstream>
#include <direct.h>
#include <string>
using namespace std;

//void Course::Export_Class(string filename)
//{
//    ofstream file;
//    file.open(filename);
//
//    // File header
//    file << "No,Student ID,First name,Last name" << "\n";
//
//
//    Student* current = StudentList.HeadS;
//    while (current) 
//    {
//        file << current->No << ",";
//        file << current->ID << ",";
//        file << current->firstname << ",";
//        file << current->lastname << ",";
//
//        current = current->pNext;
//    }
//
//    file.close();
//
//    cout << "Finished exporting to " << filename << ".\n";
//}
//
//void Course::Import_Scoreboard(string filename)
//{
//    ifstream file(filename);
//
//    // Declare a string variable to store each line of the file
//    string line;
//
//    // File header
//    getline(file, line);
//
//    while (getline(file, line)) 
//    {
//        int no, id;
//        string firstname, lastname;
//        double totalMark, finalMark, midtermMark, otherMark;
//
//    }
//
//    file.close();
//}
course::course(string id, course* pNext) :
	id(id), pNext(pNext) {}

void semester::addCourse(course*& pHeadCourses)
{
	ifstream fin;
	ofstream fout;
	cout << "Enter the schoolyear: ";
	string year; getline(cin, year);
	cout << "Enter the semester: ";
	string semester; getline(cin, semester);
	char choice = 'Y';
	while (choice == 'Y' || choice == 'y')
	{
		cout << "Enter the name of the course: ";		// get information about the course
		string name; getline(cin, name, '\n');
		cout << "Enter the course's ID: ";
		string ID; getline(cin, ID);
		cout << "Enter the classname: ";
		string className; getline(cin, className);
		cout << "Enter the lecturer of the course: ";
		string lecturer; getline(cin, lecturer);
		cout << "Input the course's credit: ";
		int credit; cin >> credit;
		cout << "Input the maximum student of this course: ";
		int maxStudent; cin >> maxStudent;
		cin.ignore();
		cout << "Which day will the course be performed? ";
		string weekDay; getline(cin, weekDay);
		cout << "Enter the session that the course will be performed (1: 07:30, 2: 09:30, 3: 13:30, 4: 15:30): ";
		int session; cin >> session;
		course* newCourse = new course(ID, nullptr);
		newCourse->pNext = pHeadCourses;
		pHeadCourses = newCourse;
		// save course ID to textfile

		fin.open("../SchoolYear/" + year + "/Semester" + semester + "/course.txt");
		if (!fin)
		{
			cout << "This schoolyear or semester doesn't exist! Please try again!";
			return;
		}
		fout.open("../SchoolYear/" + year + "/Semester" + semester + "/course.txt", ios::app);
		fin.close();
		fout << ID << endl;
		fout.close();
		saveCoursetoFolder(name, ID, className, lecturer, credit, maxStudent, weekDay, session, year, semester);	// function call
		cout << "Would you like to add more courses for this semester? Enter Y (or y) to continue adding or enter N (or n) to stop the process: ";
		cin >> choice;
		cin.ignore();
	}
}

void course::loadCourse(course*& pHeadCourses)
{
	ifstream fin;
	ofstream fout;
	cout << "Enter the schoolyear: ";
	string year; getline(cin, year);
	cout << "Enter the semester: ";
	string semester; getline(cin, semester);
	fin.open("../SchoolYear/" + year + "/Semester" + semester + "/course.txt");
	if (!fin)
	{
		cout << "Error loading course! Please try again.";
		return;
	}
	while (!fin.eof())
	{
		string id;
		getline(fin, id);
		course* pCourse = new course(id, nullptr);
		pCourse->pNext = pHeadCourses;
		pHeadCourses = pCourse;
	}
}
void semester::saveCoursetoFolder(string& name, string& id, string& className, string& lecturer, int& credit, int& maxStudent, string& weekDay, int& session, string& year, string& semester)
{
	ifstream fin;
	ofstream fout;
	if (_mkdir(("../SchoolYear/" + year + "/Semester" + semester + "/" + id).c_str()));	// create course folder
	fout.open("../SchoolYear/" + year + "/Semester" + semester + "/" + id + "/information.txt");
	fout << id << endl;
	fout << name << endl;
	fout << className << endl;
	fout << lecturer << endl;
	fout << credit << endl;
	fout << maxStudent << endl;
	fout << weekDay << endl;
	fout << session;
	fout.close();
}
void course::viewCourse(course*& pHeadCourses)
{
	course* curCourse = pHeadCourses;
	cout << "List of course: " << endl;
	while (curCourse != nullptr)
	{
		cout << curCourse->id << endl;
		curCourse = curCourse->pNext;
	}
}
void course::deleteCourse(course*& pHeadCourses)
{
	while (pHeadCourses != nullptr)
	{
		course* temp = pHeadCourses;
		pHeadCourses = pHeadCourses->pNext;
		delete temp;
	}
}
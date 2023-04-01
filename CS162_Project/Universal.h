#pragma once
#include <iostream>
#include <string>
using namespace std;

//struct Date {
//	int day;
//	int month;
//	int year;
//
//	void GetDate(int& day, int& month, int& year);
//};
//
//class Course;
//
//class Student {
//public:
//	//attribute
//	int No;
//	string ID;
//	string firstname, lastname;
//	bool Gender; //0 for male, 1 for female
//	Date DOB;
//	string Social_ID;
//	Course* CourseList;
//
//	Student* pNext;
//
//	//Constructor
//	Student(int no, string id, string firstname, string lastname,
//		bool gender, Date dob, string socialId) :
//		No(no), ID(id), firstname(firstname), lastname(lastname), Gender(gender),
//		DOB(dob), Social_ID(socialId), CourseList(nullptr), pNext(nullptr) {}
//
//	//function	
//	void viewProfile(Student*& student, string username);
//	void view_Course();
//	void view_Score();
//};
//
//class Class {
//public:
//	//a linked list of student
//	Student* HeadS;
//	Class* pNext = nullptr;
//	char Year[2]{}; // Ex: 21, 22, 23
//	char Name[5]{}; // Ex: APCS, VP, CLC
//	char Subclass{}; // Ex: 1, 2, 3
//
//	//Constructor
//	Class(char cYear[], char cName[], char cSubclass, Student*& headS);
//
//	//function
//	void Add_Student(std::ifstream& fin, std::string username, Student*& student);
//	void Remove_Student();
//	void deleteStudentList(Student*& student);
//};
//
////class Course {
////private:
////	string ID;
////	string course_name;
////	string class_name;
////	string lecturer;
////	int credits;
////	int max_student = 50;
////	string day, session;
////	//(MON / TUE / WED / THU / FRI / SAT
////	//S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30))
////	Class StudentList;
////
////public:
////	Course* pNext;
////	//Constructor
////	Course();
////	//function
////	void Add_Course();
////	void Delete_Course();
////	void View_Course();
////	void Update_Course();
////	void Export_Class(string filename);
////	void Import_Scoreboard(string filename);
////
////};
////
////class Semester;
//
//class SchoolYear
//{
//private:
//	Semester* SemList; //dynamic array
//	Class* ClassList; //linked list 
//	SchoolYear* pNext = nullptr;
//	int SYear;
//
//public:
//	//Constructor
//	SchoolYear(int cYear, Semester*& cSemList, Class*& cClassList, SchoolYear* pHead);
//
//	//Function
//	void Create_SchoolYear();
//	void delete_SchoolYear();
//
//	// Classes section
//	void Add_Classes();
//};
//
//class Semester
//{
//private:
//	int Sem;
//
//public:
//	SchoolYear* Year; //hay la dung int thoi?
//	Course* DeCourseList; // default course
//	Date StartDate, EndDate;
//
//	//Constructor
//	Semester() {};
//	Semester(SchoolYear* cYear, Date cStartDate, Date cEndDate, Course* cDeCourse);
//	//Function
//	void Create_Semester(Semester*& cSemester);
//	void Delete_Semester();
//};


struct Course_Score {
	Course* CoursePointer;
	double total;
	double midterm;
	double final;
	double other;
};

struct Student_Score {
	Student* StudentPointer;
	double total;
	double midterm;
	double final;
	double other;
};








class course
{
public:
	course* pNext;
private:
	string name;
	string id;
	string className;
	string lecturer;
	int credit;
	int maxStudent;
	int weekDay;
	int session;
};
class date
{
public:
	date(int Month, int Day, int Year);
private:
	int month;
	int day;
	int year;
};
class semester
{
public:
	semester(int Sem, int Day1, int Month1, int Year1, int Day2, int Month2, int Year2);
	void addCourse();
private:
	course* pHeadCourses = nullptr;
	date startDate, endDate;
	int sem;
};

class schoolYear
{
public:
	schoolYear* pNext;
	schoolYear(string time, schoolYear* pointer);
	schoolYear();
	string getYear();
	bool createSemester();
private:
	semester** arrSemester = new semester * [3];
	string year;
};
class school
{
public:
	void createSchoolYear();
	void createSemesterFromSchoolYear();
private:
	schoolYear* pHeadSchoolYear = nullptr;
	schoolYear* pTailSchoolYear = nullptr;
};
class student
{
public:
	student(int No, string Id, string FirstName, string MiddleName, string LastName, string SocialId, bool Gender, student* pointer);
	int no;
	string id, firstName, middleName, lastName, socialId;
	bool gender;
	student* pNext;
};
class scoreList
{
public:
	course* score = nullptr;
private:
	double total;
	double midTerm;
	double final;
	double gpa;
};


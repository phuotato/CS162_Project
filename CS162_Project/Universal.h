#include <iostream>
#include <string>
#include <fstream>
#include <direct.h>
using namespace std;
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
	void getDate();
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
	int getSem();
	semester* pNext;
	date getStartDate();
	date getEndDate();
private:
	course* pHeadCourses = nullptr;
	date startDate, endDate;
	int sem;
};

class schoolYear
{
public:
	schoolYear(string time, schoolYear* pointer);
	schoolYear();
	string getYear();
	bool createSemester();
	void showSemester();
	schoolYear* pNext;
private:
	semester** arrSemester = new semester * [3] {};
	string year;
};
class school
{
public:
	void createSchoolYear();
	void createSemesterFromSchoolYear();
	void deleteSchoolYear();
	void showSchoolYear();
	void loadFile();
	bool checkExistSchoolYear(string year);
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
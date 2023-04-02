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
	int getDay();
	int getMonth();
	int getYear();
private:
	int day;
	int month;
	int year;
};
class semester
{
public:
	//definition for constructor
	semester(int Sem, int Day1, int Month1, int Year1, int Day2, int Month2, int Year2);
	semester();

	//functions
	void addCourse();
	int getSem();
	void getInformation();

	//variables
	semester* pNext;
private:
	course* pHeadCourses = nullptr;
	date startDate, endDate;
	int sem;
};

class schoolYear
{
public:
	//definition for constructor
	schoolYear(string time, schoolYear* pointer);
	schoolYear();

	//functions
	string getYear();
	void createSemester(string year);
	void loadFile(string year);
	bool checkExistSemester(int sem);
	semester* getSemester();

	//variables
	schoolYear* pNext;
private:
	semester* pHeadSemester;
	semester* pTailSemester;
	string year;
};
class school
{
public:
	//functions
	void createSchoolYear();
	void deleteSchoolYear();
	void showSchoolYear();
	void createSemesterFromSchoolYear(); //Edit while running app - Add more semester
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
#pragma once
#include "Universal.h"
#include "Graphic.h"
#include "Student.h"
class course
{
private:
	struct studentScore {
		std::string studentID;
		std::string firstName;
		std::string lastName;
		double totalMark, finalMark, midtermMark, otherMark;
		studentScore* pNext;
	};
public:
	//constructor
	course(std::string id, std::string name, std::string className, std::string lecturer, int credit, int maxStudent, std::string weekDay, int session);
	std::string id, name, className, lecturer, weekDay;
	int credit, maxStudent, session;
	
	studentScore* hScore = nullptr; //score total
	course* pNext = nullptr;
	student* pHeadStudent = nullptr;
	student* pTailStudent = nullptr;

	//function
	void updateCourse();
	void addStudentMenu();
	void addStudent(int choice);
	void deleteStudent();
	void showStudent();
	void showInfo();
	void deleteStudentCourseList();

	//Show Functions
	/*void showingScoreOfClassList(student* pHead);
	void showScoreBoardOfClass(studentScore*& curScore, course*& cur, short range, short& Pcur);
	int getAllScore();
	void showPScoreBoardOfClass(studentScore*& curScore, course*& cur, short range, short& Pcur);

	void showGPABoardOfClass();*/

	//scoreboard functions
	void ExportClass();
	void ImportScoreboard();
	void updateStudentResult();
	void ViewScoreboard();
	void saveIndividualScore(course* curCourse);

	// Supportive function
	bool checkExistScoringFile(std::string direct);
	void saveStudentinCourse(std::string path);
	void loadStudentInCourse();
	void ChooseGPARTotal();

	//show Student
	void showingStudentList();
	void showStudent(student*& pHead, short range, short& Pcur);
	int getAllStudent();
	void showPStudent(student*& pHead, short range, short& Pcur);
};

int compareString(std::string c, std::string d, std::string a, std::string b);
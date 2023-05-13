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
	
	studentScore* hScore = nullptr;
	course* pNext = nullptr;
	student* pHeadStudent = nullptr;
	student* pTailStudent = nullptr;
	//function
	
	
	void updateCourse();
	void addStudentMenu();
	void addStudent(int choice);
	void showStudent();
	void showInfo();
	//scoreboard functions
	void ExportClass();
	void ImportScoreboard();
	void showScoreBoardOfClass();
	void updateStudentResult();
	void ViewScoreboard();
	void saveIndividualScore(course* curCourse);

	// Supportive function
	bool checkExistScoringFile(std::string direct);
	void saveIndividualScore();
	void saveStudentinCourse(std::string path);
	void loadStudentInCourse();

	//show Student
	void showingStudentList();
	void showStudent(student*& pHead, short range, short& Pcur);
	int getAllStudent();
	void showPStudent(student*& pHead, short range, short& Pcur);
};

int compareString(std::string a, std::string b, std::string c, std::string d);
#pragma once
#include "Universal.h"
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
	student* pHeadStudent = nullptr;
	student* pTailStudent = nullptr;
public:
	//constructor
	course(std::string id, std::string name, std::string className, std::string lecturer, int credit, int maxStudent, int weekDay, int session);
	std::string id, name, className, lecturer;
	int credit, maxStudent, weekDay, session;
	
	studentScore* hScore = nullptr;
	course* pNext = nullptr;

	//function
	void ExportClass();
	void ImportScoreboard();
	void ViewScoreBoard();
	void updateCourse();
	void showInformation();
	void addStudent();
	void addStudent(int choice);
	void loadClass();
	void showStudent();
};

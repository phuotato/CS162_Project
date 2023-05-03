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
	course(std::string id, std::string name, std::string className, std::string lecturer, int credit, int maxStudent, int weekDay, int session);
	std::string id, name, className, lecturer;
	int credit, maxStudent, weekDay, session;
	
	studentScore* hScore = nullptr;
	course* pNext = nullptr;
	student* pHeadStudent = nullptr;
	student* pTailStudent = nullptr;
	//function
	
	void ExportClass();
	void ImportScoreboard();
	void updateCourse();
	void addStudentMenu();
	void addStudent(int choice);
	void showStudent();
	void showInfo();
	void updateStudentResult();
	void ViewScoreboard();
	void saveIndividualScore();

};

int compareString(std::string a, std::string b, std::string c, std::string d);
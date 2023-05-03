#pragma once
#include "Universal.h"
#include "Graphic.h"
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

	//function
	
	void updateCourse();
	void ExportClass();
	void ImportScoreboard();
	void updateStudentResult();
	void ViewScoreboard();
	void saveIndividualScore();

};

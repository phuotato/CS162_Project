#pragma once
#include "Universal.h"
class course
{
private:
	struct studentScore {
		int No;
		std::string studentID;
		std::string firstName;
		std::string lastName;
		double totalMark, finalMark, midtermMark, otherMark;
		studentScore* pNext;
	};
public:
	std::string id, name, className, lecturer;
	int credit, maxStudent, weekDay, session;
	
	studentScore* hScore;
	course* pNext = nullptr;

	//function
	void ExportClass(std::string filename);
	void ImportScoreboard(std::string filename);
};

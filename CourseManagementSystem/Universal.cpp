//setting up all linked lists used in this program
#include "SchoolYear.h"
#include "Class.h"
#include "Semester.h"
#include "Graphic.h"
#include"Display.h"


//Declare global variables
schoolYear* pHeadSchoolYear = nullptr;
schoolYear* pTailSchoolYear = nullptr;
schoolYear* curSchoolYear = nullptr;

semester* curSemester = nullptr;

course* curCourse = nullptr;

Class* pHeadClass = nullptr;
Class* pTailClass = nullptr;
Class* curClass = nullptr;
int mid = getMidColumns();
void deleteData()
{
	if(pHeadSchoolYear && pHeadSchoolYear->pHeadSemester && pHeadSchoolYear->pHeadSemester->pHeadCourse)
	{
		pHeadSchoolYear->pHeadSemester->pHeadCourse->deleteStudentCourseList();
		pHeadSchoolYear->pHeadSemester->pHeadCourse->deleteCourseList();
	}
	if (pHeadSchoolYear)
	{
		pHeadSchoolYear->deleteSemesterList();
		pHeadSchoolYear->deleteSchoolYear();
	}
	if(pHeadClass)
	{
		pHeadClass->deleteStudentList();
		pHeadClass->deleteClass();
	}
}

void exitProgram()
{
	deleteData();
	drawExitBox();
	exit(0);
}

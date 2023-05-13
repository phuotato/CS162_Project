//setting up all linked lists used in this program
#include "SchoolYear.h"
#include "Class.h"
#include "Semester.h"
#include "Graphic.h"


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
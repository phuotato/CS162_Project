//setting up all linked lists used in this program
#include "SchoolYear.h"
#include "Class.h"
#include "Semester.h"


//Declare global variables
schoolYear* pHeadSchoolYear = nullptr;
schoolYear* pTailSchoolYear = nullptr;
schoolYear* curSchoolYear = nullptr;

semester* curSemester;

Class* pHeadClass = nullptr;
Class* pTailClass = nullptr;
Class* curClass = nullptr;
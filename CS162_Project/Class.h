#pragma once
#include "Student.h"

class Class{
public:
	//a linked list of student
	Student* headS;

	// whether Class is to be stored in array or linked list will be discussed

	//function
	void Add_Student();
	void Remove_Student();
};
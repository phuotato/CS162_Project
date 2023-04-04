#pragma once
#include "Universal.h"
#include <iostream>
#include <fstream>
#include <direct.h>
std::ifstream fin;
std::ofstream fout;

//Initialize extern variables
SchoolYear* pHeadSchoolYear = nullptr;
SchoolYear* pTailSchoolYear = nullptr;

//Constructor for SchoolYear
SchoolYear::SchoolYear(std::string time, SchoolYear* pointer) :year(time), pNext(pointer) {}
SchoolYear::SchoolYear() {}


//Create SchoolYear


void SchoolYear::createSchoolYear()
{
	loadFile();
	bool flag = 1;
	while (true)
	{
		std::cout << "Enter your school year you want to create: ";
		std::string year; getline(std::cin, year);
		if (checkExistSchoolYear(year))
		{
			//Create a new schoolyear and store in linked list
			fout.open("../School Year/all school year.txt", std::ios::app);				//Open file stored all year of school
			fout << std::endl << year;													//Write down the schoolyear
			fout.close();

			//Check folder and write down information for the schoolyear
			if (_mkdir(("../School Year/" + year).c_str()));
			fout.open("../School Year/" + year + "/all semester.txt", std::ios::app);
			fout.close();

			if (!pHeadSchoolYear) pHeadSchoolYear = new SchoolYear(year, nullptr);
			SchoolYear* tmp = pHeadSchoolYear->pNext;
			tmp = new SchoolYear(year, nullptr);
			pTailSchoolYear->pNext = tmp;
			pTailSchoolYear = tmp;
			if (!pHeadSchoolYear) pHeadSchoolYear = pTailSchoolYear;
			flag = 1;
		}
		else
		{
			std::cout << "This school year is already created, please enter another school year\n";
			flag = 0;
		}
	}
	if (flag)
	{
		std::cout << "Create succesfully\n";
		std::cout << "Do you want to add more school year:(Y/N || y/n) ";
		char choice; std::cin >> choice;
		std::cin.ignore();
		if (choice == 'N' || choice == 'n')
			return;
	}
}

void SchoolYear::loadFile()
{
	fin.open("../School Year/all school year.txt");
	while (!fin.eof())
	{
		std::string year;
		getline(fin, year);
		if (year == "")																		//Check if the file is empty or not
			return;
		if (!pHeadSchoolYear)
		{
			pHeadSchoolYear = new SchoolYear(year, nullptr);
			pTailSchoolYear = pHeadSchoolYear;
		}
		else
		{
			SchoolYear* tmp = new SchoolYear(year, nullptr);
			pTailSchoolYear->pNext = tmp;
			pTailSchoolYear = tmp;
		}
	}
}

bool SchoolYear::checkExistSchoolYear(std::string year)
{
	if (pHeadSchoolYear)
	{
		for (SchoolYear* cur = pHeadSchoolYear; cur; cur = cur->pNext)
		{
			if (cur->getYear() == year)
				return 0;
		}
	}
	return 1;
}


//Delete SchoolYear


void SchoolYear::deleteSchoolYear()
{
	for (pHeadSchoolYear; pHeadSchoolYear;)
	{
		//delete semester
		//for (semester* pHead = pHeadSchoolYear->getSemester(); pHead;) {
		//	semester* tmp = pHead->pNext;
		//	delete pHead;
		//	pHead = tmp;
		//}

		//delete schoolYear
		SchoolYear* tmp = pHeadSchoolYear->pNext;
		delete pHeadSchoolYear;
		pHeadSchoolYear = tmp;

	}
}


//Show SchoolYear


void SchoolYear::showSchoolYear()
{
	for (SchoolYear* cur = pHeadSchoolYear; cur; cur = cur->pNext)
		std::cout << cur->getYear() << " ";
}


//Create&Information Class

//Constructor for Class
Class::Class(std::string Name) :Name(Name) {}

//Functions for Class
void SchoolYear::Create_Information_Class() {
	for (SchoolYear* cur = pHeadSchoolYear; cur; cur = cur->pNext) {
		std::string year = cur->getYear();
		while (true) {
			fin.open(".. /School Year/" + year + "/Class.txt");
			if (!fin.eof()) return;
			std::string ClassName;
			getline(fin, ClassName, ' ');
			if (ClassName == ".") break;
			fin.ignore();

			if (!pHeadClass) pHeadClass = new Class("");
			Class* tmp = pHeadClass;
			tmp->pNext = new Class(ClassName);

			pTailClass = tmp;
			if (pHeadClass->getName() == "") delete pHeadClass;

			fin.close();
		}

	}

}


//Other functions
std::string Class::getName() {
	return Name;
}

std::string SchoolYear::getYear()
{
	return year;
}
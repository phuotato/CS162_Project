#include "Universal.h"
#include "SchoolYear.h"
#include "Student.h"
#include "Date.h"
#include "Course.h"
#include "Graphic.h"
#include "Class.h"
#include "Display.h"

//Global variable
extern schoolYear* pHeadSchoolYear;
extern schoolYear* curSchoolYear;
extern schoolYear* pTailSchoolYear;
extern Class* pHeadClass;
extern Class* curClass;
extern Class* pTailClass;
extern int mid;

void student::viewProfile_Staff()
{
    char opt = 'Y';
    std::cin.ignore();                  //ignore the \n
    while (opt == 'Y' || opt == 'y')
    {
        system("cls");
        std::string username;
        std::cout << "Input the student ID: ";
        std::getline(std::cin, username);
        std::ifstream read;
        read.open("../Data/StudentProfile/" + username + ".csv");
        if (!read)
        {
            std::cout << "The information of this student isn't available right now. Please complete the information to see later" << "\n";
            std::cout << "\n";  // split 
            std::cout << "Enter Y (or y) to continue viewing." << "\n";
            std::cout << "Enter N (or N) to stop." << "\n";
            std::cout << "Your choice -> ";
            std::cin >> opt;
            std::cin.ignore();
            continue;
        }
        std::string id, firstname, lastname, socialId;
        std::string getNO;
        std::getline(read, getNO, ',');
        std::getline(read, id, ',');
        std::getline(read, firstname, ',');
        std::getline(read, lastname, ',');
        std::string getGender;
        std::getline(read, getGender, ',');
        std::string getDay, getMonth, getYear;
        std::getline(read, getDay, '/');
        std::getline(read, getMonth, '/');
        std::getline(read, getYear, ',');
        std::getline(read, socialId, ',');
        std::string classcode;
        std::getline(read, classcode, '\n');
        read.close();
        std::cout << "No: " << getNO << "\n";
        std::cout << "Student ID: " << id << "\n";
        std::cout << "Name: " << firstname << " " << lastname << "\n";
        std::cout << "Class: " << classcode << "\n";
        std::cout << "Gender: ";
        if (getGender == "0")
            std::cout << "Male" << "\n";
        else
            std::cout << "Female" << "\n";
        std::cout << "Date of birth: " << getDay << "/" << getMonth << "/" << getYear << "\n";
        std::cout << "Social ID: " << socialId << "\n";
        std::cout << "Would you like to view other information of another student?" << "\n";
        std::cout << "\n";
        std::cout << "Enter Y (or y) to continue viewing." << "\n";
        std::cout << "Enter N (or N) to stop." << "\n";
        std::cout << "Your choice -> ";
        std::cin >> opt;
        std::cin.ignore();
    }

    std::cout << std::endl;
    std::cout << "Process done! The system will go back to the menu." << std::endl;
    system("pause");
}

void student::viewProfile_Student(std::string username)
{
    std::ifstream read;
    read.open("../Data/StudentProfile/" + username + ".csv");
    if (!read)
    {
        std::cout << "Your profile is not available to view now!" << "\n";
        return;
    }
    std::string id, firstname, lastname, socialId;
    std::string getNO;
    std::getline(read, getNO, ',');
    std::getline(read, id, ',');
    std::getline(read, firstname, ',');
    std::getline(read, lastname, ',');
    std::string getDay, getMonth, getYear;
    std::string getGender;
    std::getline(read, getGender, ',');
    std::getline(read, getDay, '/');
    std::getline(read, getMonth, '/');
    std::getline(read, getYear, ',');
    std::getline(read, socialId, ',');
    std::string classcode;
    std::getline(read, classcode);
    read.close();
    std::cout << "No: " << getNO << "\n";
    std::cout << "Student ID: " << id << "\n";
    std::cout << "Name: " << firstname << " " << lastname << "\n";
    std::cout << "Gender: ";
    if (getGender == "0")
        std::cout << "Male" << "\n";
    else
        std::cout << "Female" << "\n";
    std::cout << "Date of birth: " << getDay << "/" << getMonth << "/" << getYear << "\n";
    std::cout << "Social ID: " << socialId << "\n";

    std::cout << std::endl;
    std::cout << "Process done! The system will go back to the menu." << std::endl;
    system("pause");
}
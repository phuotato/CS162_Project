#include "Universal.h"
#include "Student.h"
#include "Date.h"
#include "Course.h"
#include "Graphic.h"

student* pStudent = nullptr;
void student::addStudentto1stClass_Console(student*& headS)
{
    std::cout << "Enter your class code (Example: 22TT2, 22TT1, 21CLC06, 20VP,...):  ";
    std::string classcode;
    std::cin.ignore();
    std::getline(std::cin, classcode);
    char choice = 'N';
    while (choice == 'N' || choice == 'n')
    {
        int no;
        std::string id, firstname, lastname, socialId;
        bool gender;
        date dob;
        std::cout << "Student: ";
        std::getline(std::cin, id);
        std::string getNO;
        std::cout << "No: ";
        std::getline(std::cin, getNO);
        no = stoi(getNO);
        std::cout << "First name: ";
        std::getline(std::cin, firstname);
        std::cout << "Last name: ";
        std::getline(std::cin, lastname);
        std::cout << "Gender: ";
        std::string getGender;
        std::getline(std::cin, getGender);
        gender = stoi(getGender);
        std::cout << "Date of birth (DD/MM/YYYY): ";
        std::string getDay, getMonth, getYear;
        std::getline(std::cin, getDay);
        std::getline(std::cin, getMonth);
        std::getline(std::cin, getYear);
        int day = stoi(getDay);
        int month = stoi(getMonth);
        int year = stoi(getYear);
        std::getline(std::cin, socialId);
        student* newStudent = new student(no, id, firstname, lastname, gender, day, month, year, socialId, nullptr);
        newStudent->pNext = headS;
        headS = newStudent;
        std::cout << "Would you like to quick inputting students by using a CSV file?" << "\n";
        std::cout << "Enter Y (or y) to quick inputting students by using a CSV file." << "\n";
        std::cout << "Enter N (or n) to continue inputting on console" << "\n";
        std::cout << "Enter 0 to stop inputting." << "\n";
        std::cin >> choice;
        std::cin.ignore();
        if (choice == 'Y' || choice == 'y')
        {
            addStudentto1stClass_File(headS);
        }
    }
}
void student::addStudentto1stClass_File(student*& headS)
{
    std::cout << "Enter your class code (Example: 22TT2, 22TT1, 21CLC06, 20VP,...):  ";
    std::string classcode;
    std::getline(std::cin, classcode);
    std::ifstream fin("../StudentProfile/" + classcode + ".csv");
    loadingPage();
    if (!fin)
    {
        system("cls");
        std::cout << "Error loading data! Please try again.";
        return;
    }
    std::string redundant;
    std::getline(fin, redundant);
    while (!fin.eof())
    {
        int no;
        std::string id, firstname, lastname, socialId;
        bool gender;
        date dob;
        std::getline(fin, id, ',');
        std::string getNO;
        std::getline(fin, getNO, ',');
        if (fin.eof())
            break;
        no = stoi(getNO);
        std::getline(fin, firstname, ',');
        std::getline(fin, lastname, ',');
        std::string getGender;
        std::getline(fin, getGender, ',');
        gender = stoi(getGender);
        std::string getDay, getMonth, getYear;
        std::getline(fin, getDay, '/');
        std::getline(fin, getMonth, '/');
        std::getline(fin, getYear, ',');
        int day = stoi(getDay);
        int month = stoi(getMonth);
        int year = stoi(getYear);
        fin.ignore();
        std::getline(fin, socialId);
        student* newStudent = new student(no, id, firstname, lastname, gender, day, month, year, socialId, nullptr);
        newStudent->pNext = headS;
        headS = newStudent;
    }
    system("cls");
    std::cout << "Add students successfully! System will go back to the menu now." << std::endl << std::endl;
    system("pause");
}

void student::viewProfile(student*& headS)
{
    student* temp = headS;
    std::string username;
    std::cout << "Input the student ID: ";
    std::cin.ignore();
    std::getline(std::cin, username);
    if (!headS)
    {
        std::cout << "No information currently! Please load the data first." << std::endl << std::endl;
        std::cout << "Process done! The system will go back to the menu." << std::endl;
        system("pause");
        return;
    }
    while (temp != nullptr)
    {
        if (temp->id == username)
        {
            std::cout << "Student ID: " << temp->id << std::endl;
            std::cout << "No: " << temp->no << std::endl;
            std::cout << "Name: " << temp->firstName << " " << temp->lastName << std::endl;
            std::cout << "Date of birth: " << temp->dob.getDay() << "/" << temp->dob.getMonth() << "/" << temp->dob.getYear() << std::endl;            std::cout << "Gender: ";
            if (temp->gender == 0)
                std::cout << "Male";
            else
                std::cout << "Female";
            std::cout << std::endl;
            std::cout << "Social ID: " << temp->socialId << std::endl;
            break;
        }
        else
            temp = temp->pNext;
    }
    if (temp == nullptr)
        std::cout << "No information about this student!" << std::endl;
    std::cout << std::endl;
    std::cout << "Process done! The system will go back to the menu." << std::endl;
    system("pause");
}

void student::deleteStudentList(student*& headS)
{
    student* cur = headS;
    while (cur != nullptr)
    {
        student* temp = cur;
        cur = cur->pNext;
        delete temp;
    }
}
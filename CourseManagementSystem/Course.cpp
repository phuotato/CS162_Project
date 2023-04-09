#include "Universal.h"
#include "Student.h"
#include "Date.h"
#include "Course.h"
#include "Graphic.h"

student* pStudent = nullptr;
void student::addStudentto1stClass(student*& headS)
{
    std::cout << "Enter your class code (Example: 22TT2, 22TT1, 21CLC06, 20VP,...):  ";
    string classcode;
    std::cin >> classcode;
    ifstream fin("../StudentProfile/" + classcode + ".csv");
    loadingPage();
    if (!fin)
    {
        system("cls");
        std::cout << "Error loading data! Please try again.";
        return;
    }
    string redundant;
    getline(fin, redundant);
    while (!fin.eof())
    {
        int no;
        string id, firstname, lastname, socialId;
        bool gender;
        date dob;
        getline(fin, id, ',');
        string getNO;
        getline(fin, getNO, ',');
        if (fin.eof())
            break;
        no = stoi(getNO);
        getline(fin, firstname, ',');
        getline(fin, lastname, ',');
        string getGender;
        getline(fin, getGender, ',');
        gender = stoi(getGender);
        string getDay, getMonth, getYear;
        getline(fin, getDay, '/');
        getline(fin, getMonth, '/');
        getline(fin, getYear, ',');
        int day = stoi(getDay);
        int month = stoi(getMonth);
        int year = stoi(getYear);
        fin.ignore();
        getline(fin, socialId);
        student* newStudent = new student(no, id, firstname, lastname, gender, day, month, year, socialId, nullptr);
        newStudent->pNext = headS;
        headS = newStudent;
    }
    system("cls");
    std::cout << "Add students successfully! System will go back to the menu now." << std::endl << std::endl;
    system("pause");
}

void student::viewProfile(student* &headS)
{
    student* temp = headS;
    string username;
    std::cout << "Input the student ID: ";
    cin.ignore();
    getline(cin, username);
    if (!headS)
    {
        std::cout << "No information currently! Please load the data first." << std::endl << std::endl;
        std::cout << "Process done! The system will go back to the menu." << std::endl;
        system("pause");
        return;
    }
    while (temp != nullptr)
    {
        if (temp->id== username)
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
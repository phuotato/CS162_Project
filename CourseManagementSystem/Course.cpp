#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "Student.h"
#include "Date.h"
#include "Course.h"
using namespace std;
student* pStudent = nullptr;
void student::addStudentto1stClass(student*& headS)
{
    cout << "Enter your class code (Example: 22TT2, 22TT1, 21CLC06, 20VP,...):  ";
    string classcode;
    cin >> classcode;
    ifstream fin("../StudentProfile/" + classcode + ".csv");
    if (!fin)
    {
        cout << "Error loading data! Please try again.";
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
    cout << "Add students successfully! System will go back to the menu now." << endl << endl;
    system("pause");
}
void student::viewProfile(student* &headS)
{
    student* temp = headS;
    string username;
    cout << "Input the student ID: ";
    cin.ignore();
    getline(cin, username);
    if (!headS)
    {
        cout << "No information currently! Please load the data first." << endl << endl;
        cout << "Process done! The system will go back to the menu." << endl;
        system("pause");
        return;
    }
    while (temp != nullptr)
    {
        if (temp->id== username)
        {
            cout << "Student ID: " << temp->id << endl;
            cout << "No: " << temp->no << endl;
            cout << "Name: " << temp->firstName << " " << temp->lastName << endl;
            cout << "Date of birth: " << temp->dob.getDay() << "/" << temp->dob.getMonth() << "/" << temp->dob.getYear() << endl;            cout << "Gender: ";
            if (temp->gender == 0)
                cout << "Male";
            else
                cout << "Female";
            cout << endl;
            cout << "Social ID: " << temp->socialId << endl;
            break;
        }
        else
            temp = temp->pNext;
    }
    if (temp == nullptr)
        cout << "No information about this student!" << endl;
    cout << endl;
    cout << "Process done! The system will go back to the menu." << endl;
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
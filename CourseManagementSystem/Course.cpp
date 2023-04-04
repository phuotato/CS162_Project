#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "Student.h"
#include "Date.h"
using namespace std;

void student::addStudentto1stClass(student*& headS) {
    cout << "Enter the classcode (Example: 22TT2, 22TT1, 21VP, 22CLC03,...): ";
    string fileName;
    getline(cin, fileName);
    ifstream fin("../StudentProfile/" + fileName + ".txt");
    if (!fin) {
        cout << "Error loading data! Please try again.";
        return;
    }
    string line;
    while (getline(fin, line)) {
        istringstream iss(line);
        int no;
        string id, firstname, lastname, socialId;
        bool gender;
        Date dob;

        if (!(iss >> no >> id >> firstname >> lastname >> gender >> dob.day >> dob.month >> dob.year >> socialId)) {
            cout << "Error reading line from file";
            continue;
        }

        student* newStudent = new student(no, id, firstname, lastname, gender, dob, socialId, nullptr);       
        newStudent->pNext = headS;
        headS = newStudent;
    }
}
void student::viewProfile(student* &headS)
{
    student* temp = headS;
    string username;
    cout << "Input the student ID ";
    getline(cin, username);
    while (temp != nullptr)
    {
        if (temp->id== username)
        {
            cout << "Student ID: " << temp->id << endl;
            cout << "No: " << temp->no << endl;
            cout << "Name: " << temp->firstName << " " << temp->lastName << endl;
            cout << "Date of birth: " << temp->dob.day << "/" << temp->dob.month << "/" << temp->dob.year << endl;
            cout << "Gender: ";
            if (temp->gender == 0)
                cout << "Male";
            else
                cout << "Female";
            cout << endl;
            cout << "Social ID: " << temp->socialId;
            break;
        }
        else
            temp = temp->pNext;
    }
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
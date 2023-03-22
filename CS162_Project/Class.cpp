#include "Universal.h"
#include <fstream>

void Class::Add_Student(ifstream& fin, string username, Student*& student)
{
    cout << "Enter your class code (Example: 22TT2, 22TT1, 21CLC06, 20VP,...):  ";
    string classcode;
    cin >> classcode;
    fin.open("StudentProfile/" + classcode + ".csv");
    if (!fin)
    {
        cout << "Error loading data! Please try again.";
        return;
    }
    string redundant;
    getline(fin, redundant);
    while (!fin.eof())
    {
        Student* newStudent = new Student;
        getline(fin, newStudent->ID, ',');
        string getNO;
        getline(fin, getNO, ',');
        if (fin.eof())
            break;
        newStudent->No = stoi(getNO);
        getline(fin, newStudent->firstname, ',');
        getline(fin, newStudent->lastname, ',');
        string getGender;
        getline(fin, getGender, ',');
        newStudent->Gender = stoi(getGender);
        string getDay, getMonth, getYear;
        getline(fin, getDay, '/');
        getline(fin, getMonth, '/');
        getline(fin, getYear, ',');
        newStudent->DOB.day = stoi(getDay);
        newStudent->DOB.month = stoi(getMonth);
        newStudent->DOB.year = stoi(getYear);
        fin.ignore();
        getline(fin, newStudent->Social_ID);
        newStudent->pNext = student;
        student = newStudent;
    }
}

void Class::deleteStudentList(Student*& student)
{
    Student* cur = student;
    while (cur != nullptr)
    {
        Student* temp = cur;
        cur = cur->pNext;
        delete temp;
    }
}
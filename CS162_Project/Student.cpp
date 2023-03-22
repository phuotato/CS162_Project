#include "Universal.h"

void viewProfile(Student*& student, string username)
{
    Student* temp = student;
    while (temp != nullptr)
    {
        if (temp->ID == username)
        {
            cout << "Student ID: " << temp->ID << endl;
            cout << "No: " << temp->No << endl;
            cout << "Name: " << temp->firstname << " " << temp->lastname << endl;
            cout << "Date of birth: " << temp->DOB.day << "/" << temp->DOB.month << "/" << temp->DOB.year << endl;
            cout << "Gender: ";
            if (temp->Gender == 0)
                cout << "Male";
            else
                cout << "Female";
            cout << endl;
            cout << "Social ID: " << temp->Social_ID;
            break;
        }
        else
            temp = temp->pNext;
    }
}
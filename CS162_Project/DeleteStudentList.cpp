#include "Universal.h"
void deleteStudentList(Student*& student)
{
    Student* cur = student;
    while (cur != nullptr)
    {
        Student* temp = cur;
        cur = cur->pNext;
        delete temp;
    }
}
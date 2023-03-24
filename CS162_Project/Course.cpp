#include "Universal.h"
#include <fstream>
using namespace std;

void Course::Export_Class(string filename)
{
    ofstream file;
    file.open(filename);

    // File header
    file << "No,Student ID,First name,Last name,Gender,Date Of Birth,Social ID" << "\n";


    Student* current = StudentList.headS;
    while (current) 
    {
        file << current->No << ",";
        file << current->ID << ",";
        file << current->firstname << ",";
        file << current->lastname << ",";
        file << current->Gender << ",";
        //chua export DOB
        file << current->Social_ID << "\n";

        current = current->pNext;
    }

    // Close the file
    file.close();

    cout << "Finished exporting to " << filename << ".\n";
}

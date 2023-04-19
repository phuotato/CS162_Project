#include "Course.h"
#include <fstream>
#include <direct.h>
#include <string>
using namespace std;

void course::ExportClass(string filename)
{
    ofstream file;
    file.open(filename);

    //File header
    file << "No,Student ID,First name,Last name" << "\n";


    studentScore* current = hScore;
    while (current) 
    {
        file << current->No << ",";
        file << current->studentID << ",";
        file << current->firstName << ",";
        file << current->lastName << ",";

        current = current->pNext;
    }

    file.close();

    cout << "Finished exporting to " << filename << ".\n";
}

void course::ImportScoreboard(string filename)
{
    ifstream file(filename);

    // Declare a string variable to store each line of the file
    string line;

    // File header
    getline(file, line);

    while (getline(file, line)) 
    {
        int no, id;
        string firstname, lastname;
        double totalMark, finalMark, midtermMark, otherMark;
    }

    file.close();
}
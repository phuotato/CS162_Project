#include "Universal.h"
#include <fstream>
using namespace std;

//void Course::Export_Class(string filename)
//{
//    ofstream file;
//    file.open(filename);
//
//    // File header
//    file << "No,Student ID,First name,Last name" << "\n";
//
//
//    Student* current = StudentList.HeadS;
//    while (current) 
//    {
//        file << current->No << ",";
//        file << current->ID << ",";
//        file << current->firstname << ",";
//        file << current->lastname << ",";
//
//        current = current->pNext;
//    }
//
//    file.close();
//
//    cout << "Finished exporting to " << filename << ".\n";
//}
//
//void Course::Import_Scoreboard(string filename)
//{
//    ifstream file(filename);
//
//    // Declare a string variable to store each line of the file
//    string line;
//
//    // File header
//    getline(file, line);
//
//    while (getline(file, line)) 
//    {
//        int no, id;
//        string firstname, lastname;
//        double totalMark, finalMark, midtermMark, otherMark;
//
//    }
//
//    file.close();
//}
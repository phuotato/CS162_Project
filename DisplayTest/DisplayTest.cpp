#include <iostream>
#include <fstream>
#include <string>
#include "Graphic.h"
using namespace std;

struct studentScore {
	std::string studentID;
	std::string firstName;
	std::string lastName;
	double totalMark, finalMark, midtermMark, otherMark;
	studentScore* pNext;
};

void ImportScoreboard(studentScore*& hScore);
void updateStudentResult(studentScore*& hScore);
void ViewScoreboard(studentScore* hScore);
void saveIndividualScore(studentScore* hScore);

int main() {
	studentScore* hScore = nullptr;
    ImportScoreboard(hScore);
    ViewScoreboard(hScore);
    cin.get();
    system("cls");
    updateStudentResult(hScore);
    ViewScoreboard(hScore);
    //saveIndividualScore(hScore);

}


void ImportScoreboard(studentScore*& hScore)
{
    std::ifstream fin("../InputFile/PH212_22TT2_scoreboard.csv");
    if (!fin)
    {
        std::cout << "Error loading file! Please try again.";
        return;
    }
    std::string header;
    std::getline(fin, header); // ignore the header row of csv

    while (!fin.eof())
    {
        std::string no, studentID, firstName, lastName, totalMarkStr, finalMarkStr, midtermMarkStr, otherMarkStr;
        double totalMark, finalMark, midtermMark, otherMark;
        std::getline(fin, no, ',');
        std::getline(fin, studentID, ',');
        if (studentID.empty() || fin.eof()) // check if we have reached the end of the file
            break;

        std::getline(fin, firstName, ',');
        std::getline(fin, lastName, ',');
        std::getline(fin, totalMarkStr, ',');
        std::getline(fin, finalMarkStr, ',');
        std::getline(fin, midtermMarkStr, ',');
        std::getline(fin, otherMarkStr, '\n');

        try {
            totalMark = std::stod(totalMarkStr);
            finalMark = std::stod(finalMarkStr);
            midtermMark = std::stod(midtermMarkStr);
            otherMark = std::stod(otherMarkStr);
        }
        catch (const std::exception& e) {
            std::cout << "Error: Invalid data format in file. Please check again.\n";
            return;
        }

        studentScore* newScore = new studentScore{ studentID, firstName, lastName, totalMark, finalMark, midtermMark, otherMark, nullptr };
        if (!hScore)
        {
            hScore = newScore;
        }
        else
        {
            studentScore* pCur = hScore;
            while (pCur->pNext)
                pCur = pCur->pNext;
            pCur->pNext = newScore;
        }
    }

    fin.close();
    std::cout << "Import successful!\n";
}

void updateStudentResult(studentScore*& hScore)
{
    std::string studentID;
    cout << "Enter student ID: ";
    getline(cin, studentID, '\n');
    studentScore* pCur = hScore;
    while (pCur && pCur->studentID != studentID)
        pCur = pCur->pNext;

    if (!pCur)
    {
        std::cout << "Student not found!\n";
        return;
    }

    std::cout << "Enter the updated scores for " << pCur->firstName << " " << pCur->lastName << " (student ID: " << pCur->studentID << ")\n";
    std::cout << "Total Mark: ";
    std::cin >> pCur->totalMark;
    std::cout << "Final Mark: ";
    std::cin >> pCur->finalMark;
    std::cout << "Midterm Mark: ";
    std::cin >> pCur->midtermMark;
    std::cout << "Other Mark: ";
    std::cin >> pCur->otherMark;

    std::cout << "Scores updated successfully!\n";
}


void ViewScoreboard(studentScore* hScore) {
    system("cls");
    // Get the number of students
    int numStudents = 0;
    studentScore* currScore = hScore;
    while (currScore != nullptr) {
        numStudents++;
        currScore = currScore->pNext;
    }

    // Draw a box around the entire scoreboard
    drawBox(1, 1, 94, numStudents + 7);

    // Print the header row
    drawBox(2, 2, 90, 3);
    gotoxy(4, 3);
    std::cout << std::left << std::setw(10) << "No."
        << std::setw(12) << "ID"
        << std::setw(20) << "Name"
        << std::setw(12) << "Total"
        << std::setw(12) << "Final"
        << std::setw(12) << "Midterm"
        << std::setw(12) << "Other";

    // Iterate over the linked list and print each student's data
    currScore = hScore;
    int row = 5; // start at row 5
    int no = 1;
    while (currScore != nullptr) {
        // Print the row number
        gotoxy(4, row);
        std::cout << std::left << std::setw(10) << no;

        // Print the student data
        std::cout << std::setw(12) << currScore->studentID
            << std::setw(20) << currScore->firstName + " " + currScore->lastName
            << std::setw(12) << currScore->totalMark
            << std::setw(12) << currScore->finalMark
            << std::setw(12) << currScore->midtermMark
            << std::setw(12) << currScore->otherMark;

        currScore = currScore->pNext;
        row++;
        no++;
    }

    // Draw a box around the bottom of the scoreboard
    drawBox(2, row, 90, 3);
}
void saveIndividualScore(studentScore* hScore) {
    // Iterate over the linked list of students
    studentScore* currScore = hScore;
    while (currScore != nullptr) {
        std::ofstream fout("../Data/StudentProfile/" + currScore->studentID + ".csv", fstream::app);

        //fout << "Course ID,Year,Semester,Total Mark,Final Mark,Midterm Mark,Other Mark\n";
        fout <<  "PH212, 2022, 2,"
            << currScore->totalMark << ","
            << currScore->finalMark << ","
            << currScore->midtermMark << ","
            << currScore->otherMark << "\n";
        fout.close();
        currScore = currScore->pNext;
    }

    std::cout << "\n\t\tSaving successful!\n";
}

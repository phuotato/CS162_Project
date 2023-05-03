#include "Course.h"
#include "schoolYear.h"
#include <fstream>
#include <direct.h>
#include <string>

//global variable
extern schoolYear* curSchoolYear;
extern semester* curSemester;

//Constructor
course::course(std::string id, std::string name, std::string className, std::string lecturer, int credit, int maxStudent, int weekDay, int session)
    :id(id), name(name), className(className), lecturer(lecturer), credit(credit), maxStudent(maxStudent), weekDay(weekDay), session(session) {};

void course::ExportClass()
{
    std::ofstream fout;
    fout.open("../Scoreboard/" + id + "_scoreboard.csv");

    //File header
    fout << "No,Student ID,First name,Last name" << "\n";

    int i = 1;
    studentScore* current = hScore;
    while (current) 
    {
        fout << i++ << ",";
        fout << current->studentID << ",";
        fout << current->firstName << ",";
        fout << current->lastName << ",";

        current = current->pNext;
    }

    fout.close();

    std::cout << "Finished exporting to " << id << "_scoreboard.csv\n";
}

void course::ImportScoreboard()
{
    std::ifstream fin("../Scoreboard/" + id + "_scoreboard.csv");
    if (!fin)
    {
        std::cout << "Error loading file! Please try again.";
        return;
    }
    std::string header;
    std::getline(fin, header); // ignore the header row of csv

    while (!fin.eof())
    {
        std::string studentID, firstName, lastName, totalMarkStr, finalMarkStr, midtermMarkStr, otherMarkStr;
        double totalMark, finalMark, midtermMark, otherMark;

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

void course::updateStudentResult()
{
    std::string studentID;
    std::cout << "Enter student ID: ";
    getline(std::cin, studentID, '\n');
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


void course::ViewScoreboard() {
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

void course::saveIndividualScore() {
    // Iterate over the linked list of students
    studentScore* currScore = hScore;
    std::ofstream fout("../Data/SchoolYear/" + curSchoolYear->year + "/" + std::to_string(curSemester->sem) + "/" + currScore->studentID + ".csv", std::fstream::app);
    fout << "Course ID,Total Mark,Final Mark,Midterm Mark,Other Mark\n";
    while (currScore != nullptr) {
        fout << currScore->totalMark << ","
            << currScore->finalMark << ","
            << currScore->midtermMark << ","
            << currScore->otherMark << "\n";
        fout.close();
        currScore = currScore->pNext;
    }

    std::cout << "\n\t\tSaving successful!\n";
}

void course::updateCourse()
{
    while(true)
    {
        system("cls");
        std::cout << "1.Id:" << id << std::endl;
        std::cout << "2.Name:" << name << std::endl;
        std::cout << "3.Class name:" << className << std::endl;
        std::cout << "4.Lecturer:" << lecturer << std::endl;
        std::cout << "5.Credit:" << credit << std::endl;
        std::cout << "6.Max student:" << maxStudent << std::endl;
        std::cout << "7.Day performed per week:" << weekDay << std::endl;
        std::cout << "8.Session:";
        switch (session)
        {
        case 1:
            std::cout << "07:30\n";
            break;
        case 2:
            std::cout << "09:30\n";
            break;
        case 3:
            std::cout << "13:30\n";
        case 4:
            std::cout << "15:30\n";
        }
        std::cout << "Chose the number you want to edit (Press enter to back):";
        std::string choice; getline(std::cin, choice);
        if (choice == "")
            break;
        int ch = stoi(choice);
        std::string New;
        int NEw;
        switch (ch)
        {
        case 1:
            std::cout << "Input the New one:";
            getline(std::cin, New);
            id = New;
            break;
        case 2:
            std::cout << "Input the New one:";
            getline(std::cin, New);
            name = New;
            break;
        case 3:
            std::cout << "Input the New one:";
            getline(std::cin, New);
            className = New;
            break;
        case 4:
            std::cout << "Input the New one:";
            getline(std::cin, New);
            lecturer = New;
            break;
        case 5:
            std::cout << "Input the New one:";
            std::cin>>NEw;
            credit = NEw;
            break;
        case 6:
            std::cout << "Input the New one:";
            std::cin >> NEw;
            maxStudent = NEw;
            break;
        case 7:
            std::cout << "Input the New one:";
            std::cin >> NEw;
            weekDay = NEw;
            break;
        case 8:
            std::cout << "Input the New one:";
            std::cin >> NEw;
            session = NEw;
            break;
        }
    }
}
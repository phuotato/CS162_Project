#include "Universal.h"
#include "SchoolYear.h"
#include "Student.h"
#include "Date.h"
#include "Course.h"
#include "Graphic.h"
#include "Class.h"
#include "Display.h"
#include <sstream>
//Global variable
extern schoolYear* pHeadSchoolYear;
extern schoolYear* curSchoolYear;
extern schoolYear* pTailSchoolYear;
extern Class* pHeadClass;
extern Class* curClass;
extern Class* pTailClass;
extern int mid;

//for student account use
extern std::string curYear;
extern int curSem;
extern std::string curSClass;



bool student::readStudentScore() {
    std::string filename = "../Data/SchoolYear/" + curYear + "/Sem" + std::to_string(curSem) + "/Class/" + curSClass + "/" + id + ".csv";
    std::ifstream fin(filename);
    if (!fin) {
        return false;
    }

    std::string line;
    std::getline(fin, line); // skip the header row

    courseScore* currScore = nullptr;

    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        std::string field;
        int fieldIndex = 0;

        std::string courseID;
        double totalMark = 0;
        double finalMark = 0;
        double midtermMark = 0;
        double otherMark = 0;

        while (std::getline(ss, field, ',')) {
            switch (fieldIndex) {
            case 0:
                courseID = field;
                break;
            case 1:
                totalMark = std::stod(field);
                break;
            case 2:
                finalMark = std::stod(field);
                break;
            case 3:
                midtermMark = std::stod(field);
                break;
            case 4:
                otherMark = std::stod(field);
                break;
            }
            fieldIndex++;
        }

        if (currScore == nullptr) {
            hScore = new courseScore{ courseID, totalMark, finalMark, midtermMark, otherMark };
            currScore = hScore;
        }
        else {
            currScore->pNext = new courseScore{ courseID, totalMark, finalMark, midtermMark, otherMark };
            currScore = currScore->pNext;
        }
    }

    fin.close();
    return true;
}


void student::viewProfile_Staff()
{
    int opt = 1;
    while (opt == 1)
    {
        system("cls");
        drawHeader();

        std::string username;
        std::cout << "\n\n"; gotox(mid - 53 / 2);
        std::cout << "Input the student ID: ";
        std::getline(std::cin, username);

        std::ifstream read;
        read.open("../Data/StudentProfile/" + username + ".csv");
        if (!read)
        {
            std::cout << "\n";
            SetColor(7, 4);
            gotox(mid - 35/2); std::cout << "There is no student with this id";
            SetColor(7, 0);
            Sleep(1000);

            //Reset the warning
            gotox(mid - 35 / 2); std::cout << "                                ";
            gotoxy(mid - 37 / 2, 12); std::cout << "Do you want to show another student?";

            opt = YNQuestions(mid - 40 / 2, 11, 40);
            continue;
        }
        std::string id, firstname, lastname, socialId;
        std::string getNO;
        std::getline(read, getNO, ',');
        std::getline(read, id, ',');
        std::getline(read, firstname, ',');
        std::getline(read, lastname, ',');

        std::string getGender;
        std::getline(read, getGender, ',');

        std::string getDay, getMonth, getYear;
        std::getline(read, getDay, '/');
        std::getline(read, getMonth, '/');
        std::getline(read, getYear, ',');
        std::getline(read, socialId, ',');

        std::string classcode;
        std::getline(read, classcode, '\n');

        read.close();
        gotox(mid - 53 / 2); std::cout << "No: " << getNO << "\n";
        gotox(mid - 53 / 2); std::cout << "Student ID: " << id << "\n";
        gotox(mid - 53 / 2); std::cout << "Name: " << firstname << " " << lastname << "\n";
        gotox(mid - 53 / 2); std::cout << "Class: " << classcode << "\n";
        gotox(mid - 53 / 2); std::cout << "Gender: ";
        if (getGender == "0")
            std::cout << "Male" << "\n";
        else
            std::cout << "Female" << "\n";

        gotox(mid - 53 / 2); std::cout << "Date of birth: " << getDay << "/" << getMonth << "/" << getYear << "\n";
        gotox(mid - 53 / 2); std::cout << "Social ID: " << socialId << "\n\n\n";
        gotox(mid - 37 / 2); std::cout << "Do you want to show another student?";

        opt = YNQuestions(mid - 40 / 2, 17, 40);
    }

}

void student::viewProfile_Student() {
    system("cls");

    drawHeader();

    std::ifstream read;
    read.open("../Data/StudentProfile/" + id + ".csv");
    if (!read) {
        SetColor(7, 12); 
        std::cout << "Your profile is not available to view now!" << "\n";
        SetColor(7, 0);
        return;
    }

    std::string studentID, firstname, lastname, socialId;
    std::string getNO;
    std::getline(read, getNO, ',');
    std::getline(read, studentID, ',');
    std::getline(read, firstname, ',');
    std::getline(read, lastname, ',');
    std::string getDay, getMonth, getYear;
    std::string getGender;
    std::getline(read, getGender, ',');
    std::getline(read, getDay, '/');
    std::getline(read, getMonth, '/');
    std::getline(read, getYear, ',');
    std::getline(read, socialId, ',');
    std::string classcode;
    std::getline(read, classcode);
    read.close();

    // Dimensions
    int boxWidth = 60;
    int boxHeight = 10;
    int boxX = mid - boxWidth / 2;
    int boxY = 10;

    drawBox(boxX, boxY, boxWidth, boxHeight);

    // Print the profile information
    SetColor(7, 9);
    gotoxy(mid - 12, boxY);
    std::cout << "Student Profile";

    SetColor(7, 0); 
    gotoxy(boxX + 2, boxY + 3);
    std::cout << "No: " << getNO;
    gotoxy(boxX + 2, boxY + 4);
    std::cout << "Student ID: " << studentID;
    gotoxy(boxX + 2, boxY + 5);
    std::cout << "Name: " << firstname << " " << lastname;
    gotoxy(boxX + 2, boxY + 6);
    std::cout << "Gender: ";
    if (getGender == "0")
        std::cout << "Male";
    else
        std::cout << "Female";
    gotoxy(boxX + 2, boxY + 7);
    std::cout << "Date of birth: " << getDay << "/" << getMonth << "/" << getYear;
    gotoxy(boxX + 2, boxY + 8);
    std::cout << "Social ID: " << socialId;

    SetColor(7, 0); 
    gotoxy(mid - 20, boxY + boxHeight + 2);
    std::cout << "Process done! The system will go back to the menu." << std::endl;
    gotoxy(mid - 15, boxY + boxHeight + 3);
    system("pause");
}


void student::viewCourseList() {
    system("cls");
    drawHeader();

    // Get the number of courses
    int numCourses = 0;
    courseScore* currScore = hScore;
    while (currScore != nullptr) {
        numCourses++;
        currScore = currScore->pNext;
    }

    int mid = getMidColumns();

    // Print the current school year and semester
    gotoxy(mid - 53/2, 10);
    SetColor(7, 9);
    std::cout << "Current School Year: " << curYear;
    gotoxy(mid - 53/2, 11);
    std::cout << "Current Semester: " << curSem;
    SetColor(7, 0);
    // Outer Box
    drawBox(mid - 25, 13, 50, numCourses + 5);

    // Print the course IDs
    currScore = hScore;
    int row = 15;
    while (currScore != nullptr) {
        gotoxy(mid - static_cast<int>(currScore->courseID.length()) / 2 - 1, row);
        std::cout << currScore->courseID;
        currScore = currScore->pNext;
        row++;
    }

    gotoxy(mid - 22, row + 4);
    system("pause");
}



void student::viewScoreboard() {
    system("cls");

    drawHeader();

    // Get the number of courses
    int numCourses = 0;
    courseScore* currScore = hScore;
    while (currScore != nullptr) {
        numCourses++;
        currScore = currScore->pNext;
    }

    int mid = getMidColumns();

    // Print the current school year and semester
    gotoxy(mid - 53 / 2, 10);
    SetColor(7, 9);
    std::cout << "Current School Year: " << curYear;
    gotoxy(mid - 53 / 2, 11);
    std::cout << "Current Semester: " << curSem;
    SetColor(7, 0);

    // Draw a box around the entire scoreboard
    drawBox(mid - 47, 13, 94, numCourses + 7);

    // Print the header row
    drawBox(mid - 45, 14, 90, 3);
    gotoxy(mid - 43, 15);
    std::cout << std::left << std::setw(10) << "No."
        << std::setw(20) << "Course ID"
        << std::setw(12) << "Total"
        << std::setw(12) << "Final"
        << std::setw(12) << "Midterm"
        << std::setw(12) << "Other";

    // Iterate over the linked list
    currScore = hScore;
    int row = 17;
    int no = 1;
    while (currScore != nullptr) {
        // Print the row number
        gotoxy(mid - 43, row);
        std::cout << std::left << std::setw(10) << no;

        // Print the course data
        std::cout << std::setw(20) << currScore->courseID
            << std::setw(12) << currScore->totalMark
            << std::setw(12) << currScore->finalMark
            << std::setw(12) << currScore->midtermMark
            << std::setw(12) << currScore->otherMark;

        currScore = currScore->pNext;
        row++;
        no++;
    }

    gotoxy(mid - 22, row + 4);
    system("pause");
}

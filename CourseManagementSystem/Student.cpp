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

void student::readStudentScore() {
    std::ifstream fin("/Data/SchoolYear/2020-2021/Sem1/22CTT2_CS162/" + id + ".csv");
    if (!fin) {
        std::cerr << "Error: could not open file.\n";
        return;
    }

    std::string line;
    std::getline(fin, line); // skip the header row

    courseScore* currScore = nullptr;

    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        std::string field;
        int fieldIndex = 0;

        std::string courseID;
        int totalMark = 0;
        int finalMark = 0;
        int midtermMark = 0;
        int otherMark = 0;

        while (std::getline(ss, field, ',')) {
            switch (fieldIndex) {
            case 0:
                courseID = field;
                break;
            case 1:
                totalMark = std::stoi(field);
                break;
            case 2:
                finalMark = std::stoi(field);
                break;
            case 3:
                midtermMark = std::stoi(field);
                break;
            case 4:
                otherMark = std::stoi(field);
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
}

void student::viewProfile_Staff()
{
    char opt = 'Y';
    std::cin.ignore();                  //ignore the \n
    while (opt == 'Y' || opt == 'y')
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

            gotox(mid - 53 / 2); std::cout << "Enter Y (or y) to continue viewing.\n";
            gotox(mid - 53 / 2); std::cout << "Enter N (or N) to stop.\n";
            gotox(mid - 53 / 2); std::cout << "Your choice -> ";
            std::cin >> opt;
            std::cin.ignore();
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
        gotox(mid - 53 / 2); std::cout << "Social ID: " << socialId << "\n";

        gotox(mid - 53 / 2); std::cout << "Would you like to view other information of another student? (Y/N):";

        std::cin >> opt;
        std::cin.ignore();
    }

    std::cout << "\n\n"; gotox(mid - 51 / 2);
    SetColor(7, 2);
    std::cout << "Process done! The system will go back to the menu.";
    SetColor(7, 0);
    Sleep(1000);
}

void student::viewProfile_Student()
{
    std::ifstream read;
    read.open("../Data/StudentProfile/" + id + ".csv");
    if (!read)
    {
        std::cout << "Your profile is not available to view now!" << "\n";
        return;
    }
    std::string id, firstname, lastname, socialId;
    std::string getNO;
    std::getline(read, getNO, ',');
    std::getline(read, id, ',');
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
    std::cout << "No: " << getNO << "\n";
    std::cout << "Student ID: " << id << "\n";
    std::cout << "Name: " << firstname << " " << lastname << "\n";
    std::cout << "Gender: ";
    if (getGender == "0")
        std::cout << "Male" << "\n";
    else
        std::cout << "Female" << "\n";
    std::cout << "Date of birth: " << getDay << "/" << getMonth << "/" << getYear << "\n";
    std::cout << "Social ID: " << socialId << "\n";

    std::cout << std::endl;
    std::cout << "Process done! The system will go back to the menu." << std::endl;
    system("pause");
}

void student::viewCourseList() {
    system("cls");

    //Get the number of courses
    int numCourses = 0;
    courseScore* currScore = hScore;
    while (currScore != nullptr) {
        numCourses++;
        currScore = currScore->pNext;
    }

    //Outer Box
    drawBox(1, 1, 50, numCourses + 5);

    // Print the header
    gotoxy(3, 2);
    std::cout << "List of Courses:";

    // Print the course IDs
    currScore = hScore;
    int row = 4;
    while (currScore != nullptr) {
        gotoxy(3, row);
        std::cout << currScore->courseID;
        currScore = currScore->pNext;
        row++;
    }

    gotoxy(3, row + 2);
    std::cout << "Press any key to go back: ";
    system("pause");
}

void student::viewScoreboard() {
    system("cls");
    // Get the number of courses
    int numCourses = 0;
    courseScore* currScore = hScore;
    while (currScore != nullptr) {
        numCourses++;
        currScore = currScore->pNext;
    }

    // Draw a box around the entire scoreboard
    drawBox(1, 1, 94, numCourses + 7);

    // Print the header row
    drawBox(2, 2, 90, 3);
    gotoxy(4, 3);
    std::cout << std::left << std::setw(10) << "No."
        << std::setw(20) << "Course ID"
        << std::setw(12) << "Total"
        << std::setw(12) << "Final"
        << std::setw(12) << "Midterm"
        << std::setw(12) << "Other";

    // Iterate over the linked list and print each course's data
    currScore = hScore;
    int row = 5; // start at row 5
    int no = 1;
    while (currScore != nullptr) {
        // Print the row number
        gotoxy(4, row);
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

    // Draw a box around the bottom of the scoreboard
    drawBox(2, row, 90, 3);
    std::cout << "\n\n\nPress any key to back:";
    system("pause");
}


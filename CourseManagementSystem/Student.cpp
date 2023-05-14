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

void student::loadProfile(std::string username){
    std::ifstream file("../Data/StudentProfile/" + username + ".csv");
    if (!file)
    {
        std::cout << "Unable to open file!" << std::endl;
        return;
    }

    std::string line;
    if (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string sNum, sGender, classcode;
        std::getline(iss, sNum, ',');
        std::getline(iss, id, ',');
        std::getline(iss, firstName, ',');
        std::getline(iss, lastName, ',');
        std::getline(iss, sGender, ',');
        std::getline(iss, dat, ',');
        std::getline(iss, socialId, ',');
        std::getline(iss, classcode);

        // Assign the classcode
        curSClass = classcode;

        //Assign the profile
        no = stoi(sNum);
        if (sGender == "0")
            gender = 0;
        else
            gender = 1;
    }
    else
    {
        std::cout << "\n\t\t\tFile is empty!" << std::endl;
        Sleep(1000);
    }

    file.close();
}

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
        int credit = 0;

        while (std::getline(ss, field, ',')) {
            switch (fieldIndex) {
            case 0:
                totalMark = std::stod(field);
                break;
            case 1:
                finalMark = std::stod(field);
                break;
            case 2:
                midtermMark = std::stod(field);
                break;
            case 3:
                otherMark = std::stod(field);
                break;
            case 4:
                courseID = field;
                break;
            case 5:
                credit = std::stoi(field);
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
void student::deleteScores() {
    courseScore* current = hScore;
    while (current != nullptr) {
        courseScore* next = current->pNext;
        delete current;
        current = next;
    }
    hScore = nullptr;
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
            gotox(mid - 35/2); std::cout << "There is no student with this id.";
            SetColor(7, 0);
            Sleep(1000);

            //Reset the warning
            gotox(mid - 35/2); std::cout << "                                 ";
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
        // Dimensions
        int boxWidth = 60;
        int boxHeight = 12;
        int boxX = mid - boxWidth / 2;
        int boxY = 10;
        gotoxy(mid - 53 / 2, 8);           
        std::cout << "                               ";

        drawBox(boxX, boxY, boxWidth, boxHeight);

        // Print the profile information
        SetColor(7, 9);
        gotoxy(mid - 10, boxY);
        std::cout << "Student Profile";

        SetColor(7, 0);
        gotoxy(boxX + 2, boxY + 2);
        std::cout << "No: " << getNO;
        gotoxy(boxX + 2, boxY + 3);
        std::cout << "Student ID: " << id;
        gotoxy(boxX + 2, boxY + 4);
        std::cout << "Name: " << lastname << " " << firstname;
        gotoxy(boxX + 2, boxY + 5);
        std::cout << "Class: " << classcode;
        gotoxy(boxX + 2, boxY + 6);
        std::cout << "Gender: " << (getGender == "0" ? "Male" : "Female");
        gotoxy(boxX + 2, boxY + 7);
        std::cout << "Date of birth: " << getDay << "/" << getMonth << "/" << getYear;
        gotoxy(boxX + 2, boxY + 8);
        std::cout << "Social ID: " << socialId;

        SetColor(7, 0);
        gotoxy(mid - 37 / 2, boxY + boxHeight + 3);
        std::cout << "Do you want to show another student?";
        opt = YNQuestions(mid - 40 / 2, boxY + boxHeight + 2, 40);
    }
}

void student::viewProfile_Student() {
    system("cls");

    drawHeader();

    // Check if the student profile is available
    if (id.empty()) {
        SetColor(7, 12);
        gotoxy(mid - 10, 10);
        std::cout << "Your profile is not available to view now!\n";
        SetColor(7, 0);
        Sleep(1000);
        return;
    }

    // Dimensions
    int boxWidth = 60;
    int boxHeight = 9;
    int boxX = mid - boxWidth / 2;
    int boxY = 10;

    drawBox(boxX, boxY, boxWidth, boxHeight);

    // Print the profile information
    SetColor(7, 9);
    gotoxy(mid - 10, boxY);
    std::cout << "Student Profile";

    SetColor(7, 0);
    gotoxy(boxX + 2, boxY + 2);
    std::cout << "Student ID: " << id;
    gotoxy(boxX + 2, boxY + 3);
    std::cout << "Name: " << lastName << " " << firstName;
    gotoxy(boxX + 2, boxY + 4);
    std::cout << "Class: " << curSClass;
    gotoxy(boxX + 2, boxY + 5);
    std::cout << "Gender: ";
    if (gender)
        std::cout << "Female";
    else
        std::cout << "Male";
    gotoxy(boxX + 2, boxY + 6);
    std::cout << "Date of birth: " << dat;
    gotoxy(boxX + 2, boxY + 7);
    std::cout << "Social ID: " << socialId;
    

    SetColor(7, 0);
    gotoxy(mid - 20, boxY + boxHeight + 3);
    std::cout << "Process done! The system will go back to the menu.\n";
    gotoxy(mid - 15, boxY + boxHeight + 4);
    system("pause");
}

bool getCourseInformation(const std::string& courseID, std::string& courseName, std::string& teacherName, int& credits, std::string& dayOfWeek, int& session) {
    // Open information.txt 
    std::string filename = "../Data/SchoolYear/" + curYear + "/Sem" + std::to_string(curSem) + "/" + courseID + "/information.txt";
    std::ifstream file(filename);
    if (!file) {
        return false;
    }
    int maxStudents; std::string courseId, classname;
    // Read the course information
    std::getline(file, courseId);
    std::getline(file, courseName);
    std::getline(file, classname);
    std::getline(file, teacherName);
    file >> credits;
    file >> maxStudents;
    file.ignore(1000, '\n');
    std::getline(file, dayOfWeek);
    //file.ignore(1000, '\n');
    file >> session;

    file.close();

    return true;
}

void student::viewCourseList() {
    system("cls");
    drawHeader();

    int mid = getMidColumns();

    // Get the number of courses
    int numCourses = 0;
    courseScore* currScore = hScore;
    while (currScore != nullptr) {
        numCourses++;
        currScore = currScore->pNext;
    }

    // Calculate the table dimensions
    int boxWidth = 100;
    int boxHeight = numCourses + 5;
    int boxX = mid - boxWidth / 2;
    int boxY = 13;

    // Outer Box
    drawBox(boxX, boxY, boxWidth, boxHeight);
    

    // Header Box
    drawBox(boxX + 1, boxY+1, boxWidth-4, 3);

    // Print the table headers
    SetColor(7, 1);
    gotoxy(boxX + 2, boxY + 2);
    std::cout << "No.";
    gotoxy(boxX + 5, boxY + 2);
    std::cout << "Course ID";
    gotoxy(boxX + 25, boxY + 2);
    std::cout << "Course Name";
    gotoxy(boxX + 52, boxY + 2);
    std::cout << "Teacher Name";
    gotoxy(boxX + 72, boxY + 2);
    std::cout << "Credits";
    gotoxy(boxX + 82, boxY + 2);
    std::cout << "Schedule";


    // Print the course information
    SetColor(7, 0);
    currScore = hScore;
    int row = boxY + 4;
    int no = 1;
    while (currScore != nullptr) {
        std::string courseName, teacherName, dayOfWeek;
        int credits, session;
        if (getCourseInformation(currScore->courseID, courseName, teacherName, credits, dayOfWeek, session)) {
            gotoxy(boxX + 2, row);
            std::cout << no;
            gotoxy(boxX + 5, row);
            std::cout << currScore->courseID;
            gotoxy(boxX + 25, row);
            std::cout << courseName;
            gotoxy(boxX + 52, row);
            std::cout << teacherName;
            gotoxy(boxX + 72, row);
            std::cout << credits;
            gotoxy(boxX + 82, row);
            std::cout << dayOfWeek << ", ";
            switch (session)            {
            case 1:
                std::cout << "07:30\n";
                break;
            case 2:
                std::cout << "09:30\n";
                break;
            case 3:
                std::cout << "13:30\n";
                break;
            case 4:
                std::cout << "15:30\n";
                break;
            }
            row++;
        }

        currScore = currScore->pNext;
    }

    gotoxy(mid - 22, row + 2);
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
    SetColor(7, 1);
    drawBox(mid - 45, 14, 90, 3);
    gotoxy(mid - 43, 15);
    std::cout << std::left << std::setw(10) << "No."
        << std::setw(20) << "Course ID"
        << std::setw(12) << "Total"
        << std::setw(12) << "Final"
        << std::setw(12) << "Midterm"
        << std::setw(12) << "Other";

    SetColor(7, 0);
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

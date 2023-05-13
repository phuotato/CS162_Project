#include "SchoolYear.h"
#include "Student.h"
#include "WelcomePage.h"
#include "ChangePassword.h"
#include "Graphic.h"
#include "Staff.h"
#include "Class.h"
#include "Display.h"
#include <sstream>


//extern student* pStudent;
//extern schoolYear* pHeadSchoolYear;
//extern schoolYear* pTailSchoolYear;
//extern schoolYear* curSchoolYear;
//extern semester* curSemester;

extern std::string username;
std::string curYear;
int curSem;
std::string curSClass;
student curStudent;

extern int mid;

void drawStudentMenu(){
    drawBox(mid - 53 / 2, 10, 52, 10);
    gotoxy(mid - 13 / 2, 11);
    std::cout << "MENU OPTIONS";

    std::cout << "\n"; drawLine(52, mid - 52 / 2);

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "1. View profile";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "2. View learning progress";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "   ";

    std::cout << "\n";
    drawLine(52, mid - 52 / 2);

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "4. Change password";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "0. Exit";

}

void learningProgress()
{
    gotoxy(mid - 30, 11);
    std::cout << "Enter the school year: ";
    std::cin >> curYear;
    gotoxy(mid - 30, 12);
    std::cout << "Enter the semester: ";
    std::cin >> curSem;

    if (!curStudent.readStudentScore()) {
        std::cerr << "You don't have any course in this semester.\n";
        system("pause");
        return;
    }

    int option = 0;
    short k = 1;
    std::string* content = new std::string[4];


    content[0] = "1. View courses";
    content[1] = "2. View scoreboard";
    content[2] = "-";
    content[3] = "0. Go back";

    while (k != 0) {
        system("cls");
        drawBox(mid - 53 / 2, 10, 52, 8);
        gotoxy(mid - 13 / 2, 11);
        std::cout << "MENU OPTIONS";

        std::cout << "\n"; drawLine(52, mid - 52 / 2);

        std::cout << "\n"; gotox(mid - 49 / 2);
        std::cout << "1. View courses";

        std::cout << "\n"; gotox(mid - 49 / 2);
        std::cout << "2. View scoreboard";

        std::cout << "\n";
        drawLine(52, mid - 52 / 2);

        std::cout << "\n"; gotox(mid - 49 / 2);
        std::cout << "0. Go back";
        option = movingBar(mid - 50 / 2, 13, 13, mid + 50 / 2, 16, 1, content);
        switch (option) {
        case 3:
            system("cls");
            drawHeader();
            curStudent.viewCourseList();
            break;
        case 2:
            system("cls");
            drawHeader();
            curStudent.viewScoreboard();
            break;

        case 0:
            //goback
            break;
        }
    }
}

void StudentMenu() {
    mid = getMidColumns();

    int option = 0;
    short k = 1;
    std::string* content = new std::string[6];

    content[0] = "1. View profile";
    content[1] = "2. View learning progress";
    content[2] = "3. View scoreboard";
    content[3] = "-";
    content[4] = "4. Change password";
    content[5] = "0. Exit";

    while (k != 0) {
        system("cls");
        drawStudentMenu();
        option = movingBar(mid - 50 / 2, 13, 13, mid + 50 / 2, 18, 1, content);
        switch (option) {
        case 5:
            system("cls");
            drawHeader();
            curStudent.viewProfile_Student();
            break;
        case 4:
            system("cls");
            drawHeader();
            learningProgress();
            break;
        case 3:
            system("cls");
            drawHeader();
            //curStudent.viewScoreboard();
            break;
        case 1:
            system("cls");
            drawHeader();
            //changePassword(fin, fout);
            break;
        case 0:
            system("cls");
            drawBox(mid - 50 / 2, 5, 50, 16);
            gotoxy(mid - 19 / 2, 10);
            std::cout << "Thank you for using\n";
            gotoxy(mid - 9 / 2, 12);
            std::cout << "FIT.HCMUS\n";
            gotoxy(mid - 19 / 2, 14);
            std::cout << "Management Program!\n\n\n\n\n\n";
            exit(0);
            break;
        }
    }

}

void loadClassFromFile()
{
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
        std::string getNO, id, firstname, lastname, socialId, getGender, getDay, getMonth, getYear, classcode;

        std::getline(iss, getNO, ',');
        std::getline(iss, id, ',');
        std::getline(iss, firstname, ',');
        std::getline(iss, lastname, ',');
        std::getline(iss, getGender, ',');
        std::getline(iss, getDay, '/');
        std::getline(iss, getMonth, '/');
        std::getline(iss, getYear, ',');
        std::getline(iss, socialId, ',');
        std::getline(iss, classcode);

        // Assign the classcode value to the student object
        curSClass = classcode;

        std::cout << "Class data loaded successfully!" << std::endl;
    }
    else
    {
        std::cout << "File is empty!" << std::endl;
    }

    file.close();
}

void StudentAcc() {
    curStudent.setID(username);
    loadClassFromFile();
    StudentMenu();
}
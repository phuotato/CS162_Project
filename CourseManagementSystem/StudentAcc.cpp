#include "SchoolYear.h"
#include "Student.h"
#include "WelcomePage.h"
#include "ChangePassword.h"
#include "Graphic.h"
#include "Staff.h"
#include "Class.h"


extern student* pStudent;
extern schoolYear* pHeadSchoolYear;
extern schoolYear* pTailSchoolYear;
extern schoolYear* curSchoolYear;
extern semester* curSemester;
extern Class* pHeadClass;
extern Class* pTailClass;
extern course* curCourse;
extern std::string username;
student curStudent(username);
extern int mid;

void drawStudentMenu(){
    drawBox(mid - 53 / 2, 10, 52, 15);
    gotoxy(mid - 13 / 2, 11);
    std::cout << "MENU OPTIONS";

    std::cout << "\n"; drawLine(52, mid - 52 / 2);

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "1. View profile";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "2. View courses";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "3. View scoreboard";

    std::cout << "\n";
    drawLine(52, mid - 52 / 2);

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "4. Change password";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "0. Exit";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "  Enter your choice: ";
}

void StudentMenu() {
    mid = getMidColumns();
    int option;
    short k = 1;
    while (k != 0) {
        system("cls");
        drawStudentMenu();
        std::cin >> option;
        switch (option) {
        case 1:
            system("cls");
            drawHeader();
            curStudent.viewProfile_Student();
            break;
        case 2:
            system("cls");
            drawHeader();
            curStudent.viewCourseList();
            break;
        case 3:
            system("cls");
            drawHeader();
            curStudent.viewScoreboard();
            break;
        case 4:
            //change password
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
        default:
            std::cout << "\n\n"; gotox(mid - 15 / 2);
            SetColor(7, 12);
            std::cout << "Invalid input.";
            SetColor(7, 0);
        }
    }
}

void StudentAcc() {
    curStudent.readStudentScore();
    StudentMenu();
}
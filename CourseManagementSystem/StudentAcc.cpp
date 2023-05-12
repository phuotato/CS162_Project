#include "SchoolYear.h"
#include "Student.h"
#include "WelcomePage.h"
#include "ChangePassword.h"
#include "Graphic.h"
#include "Staff.h"
#include "Class.h"
#include "Display.h"


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
    drawBox(mid - 53 / 2, 10, 52, 10);
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

}

void StudentMenu() {
    mid = getMidColumns();
    int option = 0;
    short k = 1;
    std::string* content = new std::string[6];
    std::ifstream fin;
    std::ofstream fout;

    content[0] = "1. View profile";
    content[1] = "2. View courses";
    content[2] = "3. View scoreboard";
    content[3] = "-";
    content[4] = "4. Change password";
    content[5] = "0. Exit";

    while (k != 0) {
        system("cls");
        drawStudentMenu();
        option = movingBar(mid - 50/2, 13, 13, mid + 50/2, 18, 1, content);
        switch (option) {
        case 5:
            system("cls");
            drawHeader();
            curStudent.viewProfile_Student();
            break;
        case 4:
            system("cls");
            drawHeader();
            curStudent.viewCourseList();
            break;
        case 3:
            system("cls");
            drawHeader();
            curStudent.viewScoreboard();
            break;
        case 1:
            system("cls");
            drawHeader();
            changePassword(fin, fout);
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

void StudentAcc() {
    curStudent.readStudentScore();
    StudentMenu();
}
#include "SchoolYear.h"
#include "Student.h"
#include "WelcomePage.h"
#include "ChangePassword.h"
#include "Graphic.h"
#include "Staff.h"
#include "Class.h"

extern std::ifstream fin;
extern std::ofstream fout;
extern student* pStudent;
extern schoolYear* pHeadSchoolYear;
extern schoolYear* pTailSchoolYear;

extern Class* pHeadClass;
extern Class* pTailClass;

int state = 1;
//1: Begin School Year
//2: Begin Semester
//3: End Semester

void BeginSchoolYearMenu() {
    SetColor(7, 1);
    std::cout << "\n\tState: Beginning of School Year. \n";
    
    //!!! chua code xong
    //!!!can them code de chon nam va the hien nam da chon
    std::cout << "\tCurrent Year: ";  

    SetColor(7, 0);
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t|                 MENU OPTIONS                     |";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t| 1. Create School Year                            |";
    std::cout << "\n\t\t| 2. Create Classes for 1st-Year Students          |";
    std::cout << "\n\t\t| 3. Add 1st-year students to 1st-year classes     |";
    std::cout << "\n\t\t| 4. Begin a new Semester                          |";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t| 5. View student profile                          |";
    // chua co 6 7
    std::cout << "\n\t\t| 6. View a list of classes                        |";
    std::cout << "\n\t\t| 7. View a list of students in a class            |";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t| 8. Change Password                               |";
    std::cout << "\n\t\t| 0. Exit                                          |";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t Enter your choice: ";
}

void BeginSchoolYear() {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);

    // Move console window to center of the screen
    system("mode con: cols=80 lines=80");
    MoveWindow(console, (GetSystemMetrics(SM_CXSCREEN) - r.right) / 2, (GetSystemMetrics(SM_CYSCREEN) - r.bottom) / 2, r.right, r.bottom, TRUE);
    int option;

    do {
        system("cls");
        drawHeader();
        BeginSchoolYearMenu();
        std::cin >> option;

        switch (option) {
        case 1:
            system("cls");
            drawHeader();
            pHeadSchoolYear->deleteSchoolYear();
            pHeadSchoolYear->createSchoolYear();
            break;
        case 2:
            pHeadClass->Choices();
            break;
        case 3: 
            system("cls");
            drawHeader();
            //temporarily removed 
            break;
        case 4: //change state to begin semester and return
            state = 2;
            return;
        case 5:
            system("cls");
            drawHeader();
            pStudent->viewProfile(pStudent);
            break;
        case 8: 
            system("cls");
            drawHeader();
            changePassword(fin, fout);
            break;
        case 0:
            system("cls");
            drawBox(25, 5, 50, 16);
            gotoxy(40, 10);
            std::cout << "Thank you for using\n";
            gotoxy(45, 12);
            std::cout << "FIT.HCMUS\n";
            gotoxy(40, 14);
            std::cout << "Management Program!\n\n\n\n\n\n";
            
            pHeadSchoolYear->deleteSchoolYear();
            pStudent->deleteStudentList(pStudent);
            exit(0);
            break;
        default:
            std::cout << "\n\t\t Invalid input.";
        }
    } while (option != 0);
}

void BeginSemesterMenu() {
    SetColor(7, 1);
    std::cout << "\n\tState: Beginning of Semester. \n";

    //!!! chua code xong
    std::cout << "\tCurrent Year: ";
    std::cout << "\n\tCurrent Semester: ";

    SetColor(7, 0);
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t|                MENU OPTIONS                      |";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t| 1. Create a semester                             |";
    std::cout << "\n\t\t| 2. Add a course                                  |";
    std::cout << "\n\t\t| 3. Update course information                     |";
    std::cout << "\n\t\t| 4. Add a student to the course                   |";
    std::cout << "\n\t\t| 5. Remove a student from the course              |";
    std::cout << "\n\t\t| 6. Delete a course                               |";
    std::cout << "\n\t\t| 7. End Semester                                  |";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t| 8. View student profile                          |";
    std::cout << "\n\t\t| 9. View a list of classes                        |";
    std::cout << "\n\t\t| 10. View a list of courses                       |";
    std::cout << "\n\t\t| 11. View a list of students in a course          |";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t| 12. Change Password                              |";
    std::cout << "\n\t\t| 0. Exit                                          |";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t Enter your choice: ";
}


void EndSemesterMenu() {
    SetColor(7, 1);
    std::cout << "\n\tState: End of Semester. \n";

    //!!! chua code xong
    std::cout << "\tCurrent Year: ";
    std::cout << "\n\tCurrent Semester: ";

    SetColor(7, 0);
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t|                MENU OPTIONS                      |";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t| 1. Export list of students in a course to CSV    |";
    std::cout << "\n\t\t| 2. Import scoreboard of a course                 |";
    std::cout << "\n\t\t| 3. View the scoreboard of a course               |";
    std::cout << "\n\t\t| 4. Update a student's result                     |";
    std::cout << "\n\t\t| 5. View the scoreboard of a class                |";
    std::cout << "\n\t\t| 6. End ?                                         |";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t| 8. View student profile                          |";
    std::cout << "\n\t\t| 9. View a list of classes                        |";
    std::cout << "\n\t\t| 10. View a list of courses                       |";
    std::cout << "\n\t\t| 11. View a list of students in a course          |";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t| 12. Change Password                              |";
    std::cout << "\n\t\t| 0. Exit                                          |";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t Enter your choice: ";
}

void EndSemester() {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);

    // Move console window to center of the screen
    system("mode con: cols=80 lines=80");
    MoveWindow(console, (GetSystemMetrics(SM_CXSCREEN) - r.right) / 2, (GetSystemMetrics(SM_CYSCREEN) - r.bottom) / 2, r.right, r.bottom, TRUE);
    int option;

    do {
        system("cls");
        drawHeader();
        EndSemesterMenu();
        std::cin >> option;

        switch (option) {
        case 1:
            std::cout << "hi";
            break;
        case 7:
            return;
        }
    } while (option != 0);
}

void BeginSemester() {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);

    // Move console window to center of the screen
    system("mode con: cols=80 lines=80");
    MoveWindow(console, (GetSystemMetrics(SM_CXSCREEN) - r.right) / 2, (GetSystemMetrics(SM_CYSCREEN) - r.bottom) / 2, r.right, r.bottom, TRUE);
    int option;

    do {
        system("cls");
        drawHeader();
        BeginSemesterMenu();
        std::cin >> option;

        switch (option) {
        case 1:
            pHeadSchoolYear->createSemester();
            break;
        case 7:
            return;
        }
    } while (option != 0);
}

void Staff()
{
    std::cin.get();
    system("cls");
    //login("../StaffAccount/");
	system("cls");
    BeginSchoolYear();
    BeginSemester();
    EndSemester();

}
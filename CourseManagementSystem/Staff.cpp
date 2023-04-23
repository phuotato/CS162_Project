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
extern schoolYear* curSchoolYear;
extern Class* pHeadClass;
extern Class* pTailClass;


void CreateSchoolYearMenu() {
    drawHeader();

    std::cout << "\n\tCreate a new school year or choose an existing one to continue.";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t| 1. Create School Year                            |";
    std::cout << "\n\t\t| 2. Choose existing School Year                   |"; //chua lam
    std::cout << "\n\t\t| 0. Exit                                          |";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t Enter your choice: ";
}

void BeginSchoolYearMenu() {
    SetColor(7, 1);
    std::cout << "\n\tState: Beginning of School Year.";
    std::cout << "\n\tCurrent Year: ";
    std::cout << curSchoolYear->year;

    SetColor(7, 0);
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t|                 MENU OPTIONS                     |";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t| 1. Create Classes for 1st-Year Students          |";
    std::cout << "\n\t\t| 2. Add 1st-year students to 1st-year classes     |";
    std::cout << "\n\t\t| 3. Begin a new Semester                          |";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t| 4. View student profile                          |";
    std::cout << "\n\t\t| 5. View a list of classes                        |"; //chua co
    std::cout << "\n\t\t| 6. View a list of students in a class            |"; //chua co
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t| 7. Change Password                               |";
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

    system("cls");
    CreateSchoolYearMenu();
    std::cin >> option;
    switch (option) {
    case 1:
        system("cls");
        drawHeader();
        pHeadSchoolYear->showSchoolYear();
        pHeadSchoolYear->createSchoolYear();
        curSchoolYear = pTailSchoolYear;
        break;
    case 2:
        system("cls");
        drawHeader();
        pHeadSchoolYear->showSchoolYear();

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
        break;
    default:
        std::cout << "\n\t\t Invalid input.";
    }

    do {
        system("cls");
        drawHeader();
        BeginSchoolYearMenu();
        std::cin >> option;

        switch (option) {
        /*case 1:
            system("cls");
            drawHeader();
            pHeadSchoolYear->deleteSchoolYear();
            pHeadSchoolYear->createSchoolYear();
            break;*/
        case 1:
            pHeadClass->Choices();
            break;
        case 2: 
            system("cls");
            drawHeader();
        //    pHeadClass->getOption();
        //    not tested yet
            break;
        case 3: //change state to begin semester and return
            return;
        case 4:
            system("cls");
            drawHeader();
            pStudent->viewProfile();
            break;
        case 7: 
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
            pHeadClass->deleteStudentList();
            exit(0);
            break;
        default:
            std::cout << "\n\t\t Invalid input.";
        }
    } while (option != 0);
}

void CreateSemesterMenu() {
    
}

void BeginSemesterMenu() {
    SetColor(7, 1);
    std::cout << "\n\tState: Beginning of Semester.";
    std::cout << "\n\tCurrent Year: ";
    std::cout << curSchoolYear->year;
    std::cout << "\n\tCurrent Semester: ";
    //chua hien semester
    

    SetColor(7, 0);
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t|                MENU OPTIONS                      |";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t| 1. Add a course                                  |";
    std::cout << "\n\t\t| 2. Update course information                     |";
    std::cout << "\n\t\t| 3. Add a student to the course                   |";
    std::cout << "\n\t\t| 4. Remove a student from the course              |";
    std::cout << "\n\t\t| 5. Delete a course                               |";
    std::cout << "\n\t\t| 6. End Semester                                  |";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t| 7. View student profile                          |";
    std::cout << "\n\t\t| 8. View a list of classes                        |";
    std::cout << "\n\t\t| 9. View a list of courses                        |";
    std::cout << "\n\t\t| 10. View a list of students in a course          |";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t| 11. Change Password                              |";
    std::cout << "\n\t\t| 0. Exit                                          |";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t Enter your choice: ";
}


void BeginSemester() {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);

    // Move console window to center of the screen
    system("mode con: cols=80 lines=80");
    MoveWindow(console, (GetSystemMetrics(SM_CXSCREEN) - r.right) / 2, (GetSystemMetrics(SM_CYSCREEN) - r.bottom) / 2, r.right, r.bottom, TRUE);
    int option;
    drawHeader();

    std::cout << "\n\tChoose a semester to continue.";
    std::cout << "\n\t\t Enter your choice: ";
    pHeadSchoolYear->createSemester();

    do {
        system("cls");
        drawHeader();
        BeginSemesterMenu();
        std::cin >> option;

        switch (option) {
        case 1:
            system("cls");
            //pHeadSchoolYear->createSemester();
            break;
        case 11:
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
            pHeadClass->deleteStudentList();
            exit(0);
            break;
        default:
            std::cout << "\n\t\t Invalid input.";
        }
    } while (option != 0);
}

void EndSemesterMenu() {
    SetColor(7, 1);
    std::cout << "\n\tState: End of Semester. \n";
    std::cout << "\tCurrent Year: ";
    std::cout << curSchoolYear->year;
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
        case 12:
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
            pHeadClass->deleteStudentList();
            exit(0);
            break;
        default:
            std::cout << "\n\t\t Invalid input.";
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
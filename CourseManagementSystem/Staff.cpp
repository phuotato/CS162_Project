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
extern semester* curSemester;
extern Class* pHeadClass;
extern Class* pTailClass;
extern course* curCourse;
extern int mid;


void BeginSemester();
void CreateSchoolYearMenu() {
    drawHeader();

    gotoxy(mid - 65 / 2, 7); std::cout <<  "Create a new school year or choose an existing one to continue.";
    gotoxy(mid - 53 / 2, 8); std::cout <<  "+--------------------------------------------------+";
    gotoxy(mid - 53 / 2, 9); std::cout <<  "| 1. Create School Year                            |";
    gotoxy(mid - 53 / 2, 10); std::cout << "| 2. Choose existing School Year                   |";
    gotoxy(mid - 53 / 2, 11); std::cout << "| 0. Exit                                          |";
    gotoxy(mid - 53 / 2, 12); std::cout << "+--------------------------------------------------+";
    gotoxy(mid - 53 / 2, 13); std::cout << "  Enter your choice: ";
}

void BeginSchoolYearMenu() {
    SetColor(7, 1);
    std::cout << "\n"; gotox(mid - 74 / 2);
    std::cout << "State: Beginning of School Year.";

    std::cout << "\n"; gotox(mid - 74 / 2);
    std::cout << "Current Year : ";
    std::cout << curSchoolYear->year;

    SetColor(7, 0);
    std::cout << "\n"; gotox(mid - 53 / 2);
    std::cout << "+--------------------------------------------------+";

    std::cout << "\n"; gotox(mid - 53 / 2);
    std::cout << "|                 MENU OPTIONS                     |";

    std::cout << "\n"; gotox(mid - 53 / 2);
    std::cout << "+--------------------------------------------------+";

    std::cout << "\n"; gotox(mid - 53 / 2);
    std::cout << "| 1. Create Classes for 1st-Year Students          |";

    std::cout << "\n"; gotox(mid - 53 / 2);
    std::cout << "| 2. Add 1st-year students to 1st-year classes     |";

    std::cout << "\n"; gotox(mid - 53 / 2);
    std::cout << "| 3. Begin a new Semester                          |";

    std::cout << "\n"; gotox(mid - 53 / 2);
    std::cout << "+--------------------------------------------------+";

    std::cout << "\n"; gotox(mid - 53 / 2);
    std::cout << "| 4. View student profile                          |";

    std::cout << "\n"; gotox(mid - 53 / 2);
    std::cout << "| 5. View a list of classes                        |"; //chua co

    std::cout << "\n"; gotox(mid - 53 / 2);
    std::cout << "| 6. View a list of students in a class            |"; //chua co

    std::cout << "\n"; gotox(mid - 53 / 2);
    std::cout << "+--------------------------------------------------+";

    std::cout << "\n"; gotox(mid - 53 / 2);
    std::cout << "| 7. Change Password                               |";

    std::cout << "\n"; gotox(mid - 53 / 2);
    std::cout << "| 8. Go back to school year                        |";

    std::cout << "\n"; gotox(mid - 53 / 2);
    std::cout << "| 0. Exit                                          |";

    std::cout << "\n"; gotox(mid - 53 / 2);
    std::cout << "+--------------------------------------------------+";

    std::cout << "\n"; gotox(mid - 53 / 2);
    std::cout << "  Enter your choice: ";
}

void SchoolYearMenu() {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);

    // Move console window to center of the screen
    set_console_size(156, 80);
    system("mode con: cols=156 lines=80");
    mid = getMidColumns();
    //MoveWindow(console, (GetSystemMetrics(SM_CXSCREEN) - r.right) / 2, (GetSystemMetrics(SM_CYSCREEN) - r.bottom) / 2, r.right, r.bottom, TRUE);
    int option;
    short k = 1;
    while (k != 0) {
        system("cls");
        pHeadSchoolYear->deleteSchoolYear();
        CreateSchoolYearMenu();
        std::cin >> option;
        switch (option) {
        case 1:
            system("cls");
            drawHeader();
            pHeadSchoolYear->createSchoolYear(k);
            curSchoolYear = pTailSchoolYear;
            break;
        case 2:
            system("cls");
            drawHeader();
            pHeadSchoolYear->chooseSchoolYear(k);
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
        default:
            std::cout << "\n\n"; gotox(mid - 15 / 2);
            SetColor(7, 12);
            std::cout << "Invalid input.";
            SetColor(7, 0);
        }
    }
}
void BeginSchoolYear (bool& flag) {
    //Resize (not automatically)
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);

    // Move console window to center of the screen
    system("mode con: cols=156 lines=80");
    mid = getMidColumns();
    int option;
    pHeadClass->LoadFile();
    pHeadClass->loadStudent();
    do {
        system("cls");
        drawHeader();
        BeginSchoolYearMenu();
        std::cin >> option;

        switch (option) {
        case 1:
            if (curSchoolYear->getYear() != pTailSchoolYear->getYear()) {
                std::cout << "\n\n"; gotox(mid - 52 / 2);
                SetColor(7, 12);
                std::cout << "Sorry! You can only add classes in the latest year.";
                SetColor(7, 0);

                Sleep(2000);
                continue;
            }
            pHeadClass->addNewClass();
            break;
        case 2: 
            system("cls");
            drawHeader();
            pHeadClass->getOption();
        
            break;
        case 3: 
            BeginSemester(); //change state to begin semester and return
            flag = 0;
            break;
        case 4:
            system("cls");
            drawHeader();
            pStudent->viewProfile();
            break;
        case 6:
            system("cls");
            drawHeader();
            pHeadClass->viewStudentList();
            break;
        case 7: 
            system("cls");
            drawHeader();
            changePassword(fin, fout);
            break;
        case 8:
            flag = 1;
            system("cls");

            pHeadSchoolYear->deleteSchoolYear();
            pHeadClass->deleteStudentList();
            return;
        case 0:
            system("cls");
            drawBox(mid - 50 / 2, 5, 50, 16);
            gotoxy(mid - 19 / 2, 10);
            std::cout << "Thank you for using\n";
            gotoxy(mid - 9 / 2, 12);
            std::cout << "FIT.HCMUS\n";
            gotoxy(mid - 19 / 2, 14);
            std::cout << "Management Program!\n\n\n\n\n\n";

            pHeadSchoolYear->deleteSchoolYear();
            pHeadClass->deleteStudentList();

            exit(0);
            break;
        default:
            std::cout << "\n\n"; gotox(mid - 15 / 2);
            SetColor(7, 12);
            std::cout << "Invalid input.";
            SetColor(7, 0);
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
    std::cout << curSemester->getSem();
    

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
    std::cout << "\n\t\t| 9: View a list of students in a class            |";
    std::cout << "\n\t\t| 10. View a list of courses                       |";
    std::cout << "\n\t\t| 11. View a list of students in a course          |";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t| 12. Change Password                              |";
    std::cout << "\n\t\t| 13. Back                                         |";
    std::cout << "\n\t\t| 0. Exit                                          |";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t Enter your choice: ";
}


void BeginSemester() {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);

    // Move console window to center of the screen
    system("mode con: cols=156 lines=80");
    MoveWindow(console, (GetSystemMetrics(SM_CXSCREEN) - r.right) / 2, (GetSystemMetrics(SM_CYSCREEN) - r.bottom) / 2, r.right, r.bottom, TRUE);
    int option, choice;
    do
    {
        system("cls");
        drawHeader();

        std::cout << "\n\tCreate a new semester or choose an existing one to continue.";
        std::cout << "\n\t\t+--------------------------------------------------+";
        std::cout << "\n\t\t| 1. Create semester                               |";
        std::cout << "\n\t\t| 2. Choose existing semester                      |"; //chua lam
        std::cout << "\n\t\t| 0. Back                                          |";
        std::cout << "\n\t\t+--------------------------------------------------+";
        std::cout << "\n\t\t Enter your choice: ";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            if (curSchoolYear->createSemester())
                break;
            else
                continue;
        case 2:
            if (curSchoolYear->showSemester())
                break;
            else
                continue;
        case 0:
            continue;
        }
        bool flag{};
        do {
            system("cls");
            drawHeader();
            BeginSemesterMenu();
            std::cin >> option;

            switch (option) {
            case 1:
                system("cls");
                curSemester->addCourse();
                break;
            case 2:
                std::cin.ignore();
                while(true)
                {
                    system("cls");
                    if(curSemester->showCourse())
                    curCourse->updateCourse();
                    else
                    break;
                }
                break;
            case 3:
                std::cin.ignore();
                while (true)
                {
                    system("cls");
                    if (curSemester->showCourse())
                        curCourse->addStudentMenu();
                    else
                        break;
                }
                break;
            case 5:
                std::cin.ignore();
                while (true)
                {
                    system("cls");
                    if (curSemester->showCourse())
                        curSemester->deleteCourse();
                    else
                        break;
                }
                break;
            case 9:
                std::cin.ignore();
                while (true)
                {
                    system("cls");
                    if (curSemester->showCourse())
                        curCourse->showInfo();
                    else
                        break;
                }
                break;
            case 10:
                std::cin.ignore();
                while (true)
                {
                    system("cls");
                    if (curSemester->showCourse())
                        curCourse->showStudent();
                    else
                        break;
                }
                break;
            case 11:
            case 7:
                system("cls");
                pStudent->viewProfile();
                break;
            case 9: 
                system("cls");
                pHeadClass->viewStudentList();
                break;
            case 12:
                system("cls");
                drawHeader();
                changePassword(fin, fout);
                break;
            case 13:
                flag = 1;
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
        } while (!flag);
    } while (choice);
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
    std::cout << "\n\t\t| 10. View a list of student in a class            |";
    std::cout << "\n\t\t| 11. View a list of courses                       |";
    std::cout << "\n\t\t| 12. View a list of students in a course          |";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t| 13. Change Password                              |";
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
        case 8:
            system("cls");
            pStudent->viewProfile();
            break;
        case 10:
            system("cls");
            pHeadClass->viewStudentList();
            break;
        case 13:
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
    bool flag = 1;
    while (flag != 0) {
        SchoolYearMenu();
        BeginSchoolYear(flag);
    }

//  BeginSemester();
    EndSemester();

}
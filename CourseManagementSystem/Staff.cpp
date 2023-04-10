#include "SchoolYear.h"
#include "Student.h"
#include "WelcomePage.h"
#include "ChangePassword.h"
#include "Graphic.h"
#include "Staff.h"

extern std::ifstream fin;
extern std::ofstream fout;
extern student* pStudent;
extern schoolYear* pHeadSchoolYear;
extern schoolYear* pTailSchoolYear;

int state = 1;
//1: Begin School Year
//2: Begin Semester
//3: End Semester

void StartSchoolYearMenu() {
    SetColor(7, 1);
    std::cout << "\n\tState: Beginning of School Year. \n";
    
    //!!! chua code xong
    //!!!can them code de chon nam va the hien nam da chon
    std::cout << "\tCurrent Year: ";  

    SetColor(7, 0);
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t|              MENU OPTIONS                        |";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t| 1. Create School Year                            |";
    std::cout << "\n\t\t| 2. Create Classes for 1st-Year Students          |";
    std::cout << "\n\t\t| 3. Add 1st-year students to 1st-year classes     |";
    std::cout << "\n\t\t| 4. Begin a new Semester                          |";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t| 5. View student profile                          |";
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
    system("mode con: cols=100 lines=80");
    MoveWindow(console, (GetSystemMetrics(SM_CXSCREEN) - r.right) / 2, (GetSystemMetrics(SM_CYSCREEN) - r.bottom) / 2, r.right, r.bottom, TRUE);
    int option;

    do {
        system("cls");
        drawHeader();
        StartSchoolYearMenu();
        cin >> option;

        switch (option) {
        case 1:
            system("cls");
            drawHeader();
            pHeadSchoolYear->loadFile();
            pHeadSchoolYear->createSchoolYear();
            break;
        case 2:
            pHeadSchoolYear->createInformationClass();
            break;
        case 3: 
            system("cls");
            drawHeader();
            pStudent->addStudentto1stClass(pStudent);
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

void Staff()
{
    cin.get();
    system("cls");
    //login("../StaffAccount/");
	system("cls");
    BeginSchoolYear();
}
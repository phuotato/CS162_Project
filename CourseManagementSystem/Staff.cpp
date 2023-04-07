#include "schoolYear.h"

using namespace std;
extern std::ifstream fin;
extern std::ofstream fout;
extern student* pStudent;
extern schoolYear* pHeadSchoolYear;
extern schoolYear* pTailSchoolYear;


void displayMenu() {
    cout << "\n\t\t-----------------------";
    cout << "\n\t\t 1. Create School Year";
    cout << "\n\t\t 2. Create Classes for 1st-Year Students";
    cout << "\n\t\t 3. Add 1st-year students to 1st-year classes";
    cout << "\n\t\t 4. View student profile";
    cout << "\n\t\t 5. Change Password";
    cout << "\n\t\t 0. Exit";
    cout << "\n\t\t-----------------------";
    cout << "\n\t\t Enter your choice: ";
}

int BeginSchoolYear() {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);

    // Move console window to center of the screen
    system("mode con: cols=100 lines=60");
    MoveWindow(console, (GetSystemMetrics(SM_CXSCREEN) - r.right) / 2, (GetSystemMetrics(SM_CYSCREEN) - r.bottom) / 2, r.right, r.bottom, TRUE);

    drawHeader();
    cout << "\n\tState: Begin of School Year. \n";
    int option;

    do {
        system("cls");
        drawHeader();
        cout << "\n\tState: Begin of School Year. \n";
        displayMenu();
        cin >> option;

        switch (option) {
        case 1:
            system("cls");
            pHeadSchoolYear->loadFile();
            pHeadSchoolYear->createSchoolYear();
            break;
        case 2:
            pHeadSchoolYear->createInformationClass();
            break;
        case 3: 
            system("cls");
            pStudent->addStudentto1stClass(pStudent);
            break;
        case 4:
            system("cls");
            pStudent->viewProfile(pStudent);
            break;
        case 5: 
            system("cls");
            changePassword(fin, fout);
            break;
        case 0:
            cout << "\n\t\t Thank you for using the College Management Program!";
            pHeadSchoolYear->deleteSchoolYear();
            pStudent->deleteStudentList(pStudent);
            exit(0);
            break;
        default:
            cout << "\n\t\t Invalid input.";
        }
    } while (option != 0);
}

void Staff()
{
    cin.get();
    system("cls");
    login("../StaffAccount/");
	system("cls");
    BeginSchoolYear();
}
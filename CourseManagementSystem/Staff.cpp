#include "Universal.h"

using namespace std;
extern std::ifstream fin;
extern std::ofstream fout;
extern student* pStudent;
extern SchoolYear* pHeadSchoolYear;
extern SchoolYear* pTailSchoolYear;

void displayHeader() {
    system("cls");
    cout << "\n\n\t\t FIT.US Management Program\n\n";
}

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
    MoveWindow(console, (GetSystemMetrics(SM_CXSCREEN) - r.right) / 2, (GetSystemMetrics(SM_CYSCREEN) - r.bottom) / 2, r.right, r.bottom, TRUE);

    displayHeader();
    int option;

    do {
        system("cls");
        displayMenu();
        cin >> option;

        switch (option) {
        case 1:
            system("cls");
            gotoxy(12, 0);
            cout << "All the year list:\n";
            pHeadSchoolYear->loadFile();
            pHeadSchoolYear->showSchoolYear();
            pHeadSchoolYear->createSchoolYear();
            break;
        case 2:
            pHeadSchoolYear->Create_Information_Class();
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
    login("../StaffAccount/");
	system("cls");
	cout << "Begin of school year: \n";
    BeginSchoolYear();
}
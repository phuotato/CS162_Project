#include "Staff.h"
using namespace std;

void displayHeader() {
    system("cls");
    cout << "\n\n\t\t FIT.US Management Program\n\n";
}

void displayMenu() {
    cout << "\n\t\t-----------------------";
    cout << "\n\t\t 1. Create School Year";
    cout << "\n\t\t 2. Create Classes for 1st-Year Students";
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
            // Code to create school year
            break;
        case 2:
            // Code to create classes for 1st-year students
            break;
        case 0:
            cout << "\n\t\t Thank you for using the College Management Program!";
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
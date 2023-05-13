#include "SchoolYear.h"
#include "Student.h"
#include "WelcomePage.h"
#include "ChangePassword.h"
#include "Graphic.h"
#include "Staff.h"
#include "Class.h"
#include "Display.h"

//global varibles
extern student* pStudent;
extern schoolYear* pHeadSchoolYear;
extern schoolYear* pTailSchoolYear;
extern schoolYear* curSchoolYear;
extern semester* curSemester;
extern Class* pHeadClass;
extern Class* pTailClass;
extern Class* curClass;
extern course* curCourse;
extern int mid;

//declare
void SchoolYearMenu(std::string*& content);
void SchoolYear();
void BeginSchoolYearMenu();
void BeginSchoolYear(bool& flag);
void CreateSemesterMenu(); //function gi day?????
void BeginSemesterMenu();
void BeginSemester();
void EndSemesterMenu();
void EndSemester();

//main
void Staff()
{
    loadingPageNotuse();
    system("cls");
    bool flag = 1;
    while (flag != 0) {
        SchoolYear();
        BeginSchoolYear(flag);
    }
}

//define
void SchoolYearMenu(std::string*& content) {
    content = new std::string[3];
    content[2] = "0. Exit";
    content[1] = "2. Choose existing School Year";
    content[0] = "1. Create School Year";

    drawHeader();
    drawBox(mid - 53 / 2, 8, 53, 9);

    gotoxy(mid - 65 / 2, 7); std::cout <<  "Create a new school year or choose an existing one to continue.";
    gotoxy(mid - 49 / 2, 10); std::cout <<  "1. Create School Year                            ";
    gotoxy(mid - 49 / 2, 12); std::cout << "2. Choose existing School Year                   ";
    gotoxy(mid - 49 / 2, 14); std::cout << "0. Exit                                          ";
}

void SchoolYear() {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);

    // Move console window to center of the screen
    set_console_size(156, 80);
    system("mode con: cols=156 lines=80");
    mid = getMidColumns();
    //MoveWindow(console, (GetSystemMetrics(SM_CXSCREEN) - r.right) / 2, (GetSystemMetrics(SM_CYSCREEN) - r.bottom) / 2, r.right, r.bottom, TRUE);
    int option = 0;
    short k = 1;
    std::string* content = nullptr;
    while (k != 0) {
        system("cls");
        pHeadSchoolYear->deleteSchoolYear();
        SchoolYearMenu(content);
        option = movingBar(mid - 51 / 2, 10, 10 + option * 2, mid + 51 / 2, 14, 2, content);

        switch (option) {
        case 2:
            system("cls");
            drawHeader();
            pHeadSchoolYear->createSchoolYear(k);
            curSchoolYear = pTailSchoolYear;
            break;
        case 1:
            system("cls");
            drawHeader();
            pHeadSchoolYear->chooseSchoolYear(k);
            break;
        case 0:
            delete[] content;
            exitProgram();
        }
    }
}

void BeginSchoolYearMenu() {

    SetColor(7, 1);
    std::cout << "\n"; gotox(mid - 74 / 2 + 15);
    std::cout << "State: Beginning of School Year.";

    std::cout << "\n"; gotox(mid - 74 / 2 + 15);
    std::cout << "Current Year : ";
    std::cout << curSchoolYear->year;

    SetColor(7, 0);
    drawBox(mid - 53 / 2, 10, 52, 15);
    gotoxy(mid - 13 / 2, 11);
    std::cout << "MENU OPTIONS";

    std::cout << "\n"; drawLine(52, mid - 52 / 2);

    std::cout << "\n"; gotox(mid - 49 / 2); //13
    std::cout << "1. Create Classes for 1st-Year Students";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "2. Add 1st-year students to 1st-year classes";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "3. Begin a new Semester";

    std::cout << "\n";
    drawLine(52, mid - 52 / 2);

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "4. View student profile";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "5. View a list of classes";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "6. View a list of students in a class";

    std::cout << "\n";
    drawLine(52, mid - 52 / 2);

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "7. Change Password";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "8. Go back to school year";

    std::cout << "\n"; gotox(mid - 49 / 2); //23
    std::cout << "0. Exit";

}

void BeginSchoolYear(bool& flag) {
    //Resize (not automatically)
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);

    // Move console window to center of the screen
    system("mode con: cols=156 lines=80");
    mid = getMidColumns();
    int option = 0;
    pHeadClass->LoadFile();
    pHeadClass->loadStudent();
    std::ifstream fin;
    std::ofstream fout;
    bool check = 0;

    std::string* content = new std::string[11];

    content[0] = "1. Create Classes for 1st-Year Students";
    content[1] = "2. Add 1st-year students to 1st-year classes";
    content[2] = "3. Begin a new Semester";
    content[3] = "-";
    content[4] = "4. View student profile";
    content[5] = "5. View a list of classes";
    content[6] = "6. View a list of students in a class";
    content[7] = "-";
    content[8] = "7. Change Password";
    content[9] = "8. Go back to school year";
    content[10] = "0. Exit";

    do {
        system("cls");
        drawHeader();
        BeginSchoolYearMenu();
        option = movingBar(mid - 51 / 2, 13, 13 + option, mid + 51 / 2, 23, 1, content);

        switch (option) {
        case 10:
            if (pHeadClass->checkLatestYear() != 0) {
                check = 1;
                pHeadClass->addNewClass();
            }
            option = 0;
            break;
        case 9: 
            if (pHeadClass->checkLatestYear() != 0) {
                system("cls");
                drawHeader();
                pHeadClass->getOption();
                check = 1;
            }
            option = 0;
            break;
        case 8:
            if (check == 1) {
                pHeadClass->deleteClass();
                pHeadClass->LoadFile();
                pHeadClass->loadStudent();
                check = 0;
            }
            BeginSemester(); //change state to begin semester and return
            flag = 0;
            option = 0;
            break;
        case 6:
            system("cls");
            drawHeader();
            pStudent->viewProfile_Staff();
            option = 0;
            break;
        case 5:
            if (check == 1) {
                pHeadClass->deleteClass();
                pHeadClass->LoadFile();
                check = 0;
            }
            pHeadClass->showingList();
            option = 0;
            break;
        case 4:
            system("cls");
            drawHeader();
            if (check == 1) {
                pHeadClass->deleteClass();
                pHeadClass->LoadFile();
                pHeadClass->loadStudent();
                check = 0;
            }
            pHeadClass->viewStudentList();
            option = 0;
            break;
        case 2:
            system("cls");
            drawHeader();
            changePassword();
            option = 0;
            break;
        case 1:
            flag = 1;
            system("cls");

            pHeadSchoolYear->deleteSchoolYear();
            //pHeadClass->deleteStudentList();
            option = 0;
            return;
        case 0:
            delete[] content;
            exitProgram();
        }
    } while (true);
}

void CreateSemesterMenu() {
    //gi z??
}

void BeginSemesterMenu() {
    SetColor(7, 1);
    std::cout << "\n"; gotox(mid - 74 / 2 + 15);
    std::cout << "State: Beginning of Semester.";

    std::cout << "\n"; gotox(mid - 74 / 2 + 15);
    std::cout << "Current Year: ";
    std::cout << curSchoolYear->year;

    std::cout << "\n"; gotox(mid - 74 / 2 + 15);
    std::cout << "Current Semester: ";
    std::cout << curSemester->getSem();
    
    SetColor(7, 0);
    drawBox(mid - 53 / 2, 11, 53, 20);

    gotoxy(mid - 13 / 2, 12);
    std::cout << "MENU OPTIONS\n";

    drawLine(53, mid - 53 / 2);
 
    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "1. Add a course";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "2. Update course information";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "3. Add a student to the course";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "4. Remove a student from the course";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "5. Delete a course";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "6. End Semester\n";
    
    drawLine(53, mid - 53 / 2);

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "7. View student profile";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "8. View a list of classes";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "9: View a list of students in a class";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "10. View a list of courses";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "11. View a list of students in a course\n";

    drawLine(53, mid - 53 / 2);

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "12. Change Password";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "13. Back";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "0. Exit";

}
void BeginSemester() {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);

    // Move console window to center of the screen
    system("mode con: cols=156 lines=80");
    MoveWindow(console, (GetSystemMetrics(SM_CXSCREEN) - r.right) / 2, (GetSystemMetrics(SM_CYSCREEN) - r.bottom) / 2, r.right, r.bottom, TRUE);
    int option, choice = 0;

    do
    {
        std::string* content = new std::string[3];
        content[0] = "1. Create semester";
        content[1] = "2. Choose existing semester";
        content[2] = "0. Back";

        system("cls");
        drawHeader();

        drawBox(mid - 53 / 2 + 8, 8, 53, 9);
        gotoxy(mid - 65 / 2 + 12, 7); std::cout << "Create a new semester or choose an existing one to continue.";
        gotoxy(mid - 49 / 2 + 8, 10); std::cout << "1. Create semester                            ";
        gotoxy(mid - 49 / 2 + 8, 12); std::cout << "2. Choose existing semester                   ";
        gotoxy(mid - 49 / 2 + 8, 14); std::cout << "0. Back                                          ";
        /*gotoxy(mid - 53 / 2 + 2, 7); std::cout << "Create a new semester or choose an existing one to continue.";
        gotoxy(mid - 53 / 2 + 2, 9); std::cout << "1. Create semester";
        gotoxy(mid - 53 / 2 + 2, 10); std::cout << "2. Choose existing semester";
        gotoxy(mid - 53 / 2 + 2, 11); std::cout << "0. Back";*/
        //choice = movingBar(mid - 51 / 2, 9, 9 + choice, mid + 53 / 2, 11, 1, content);
        choice = movingBar(mid - 51 / 2, 10, 10 + choice * 2, mid + 51 / 2, 14, 2, content);
        switch (choice)
        {
        case 2:
            if (pHeadClass->checkLatestYear() != 0) {
                if (curSchoolYear->createSemester())
                    break;
                else
                    continue;
            }
        case 1:
            if (curSchoolYear->showSemester())
                break;
            else
                continue;
        case 0:
            continue;
        }
        delete[] content;
        content = new std::string[16];
        content[0] = "1. Add a course";
        content[1] = "2. Update course information";
        content[2] = "3. Add a student to the course";
        content[3] = "4. Remove a student from the course";
        content[4] = "5. Delete a course";
        content[5] = "6. End Semester";
        content[6] = "-";
        content[7] = "7. View student profile";
        content[8] = "8. View a list of classes";
        content[9] = "9. View a list of students in a class";
        content[10] = "10. View a list of courses";
        content[11] = "11. View a list of students in a course";
        content[12] = "-";
        content[13] = "12. Change Password";
        content[14] = "13. Back";
        content[15] = "0. Exit";

        bool flag{};
        std::ifstream fin;
        std::ofstream fout;

        do {
            system("cls");
            drawHeader();
            BeginSemesterMenu();
            option = movingBar(mid - 51 / 2, 14, 14, mid + 51 / 2, 29, 1, content);

            switch (option) {
            case 15:
                system("cls");
                curSemester->addCourse();
                break;
            case 14:
                while(true)
                {
                    system("cls");
                    if(curSemester->viewCourse())
                    curCourse->updateCourse();
                    else
                    break;
                }
                break;
            case 13:
                while (true)
                {
                    system("cls");
                    if (curSemester->viewCourse())
                        curCourse->addStudentMenu();
                    else
                        break;
                }
                break;
            case 12:
                while (true)
                {
                    system("cls");
                    if (curSemester->viewCourse())
                        curCourse->deleteStudent();
                    else
                        break;
                }
                break;
            case 11:
                while (true)
                {
                    system("cls");
                    if (curSemester->viewCourse())
                        curSemester->deleteCourse();
                    else
                        break;
                }
                break;
            case 10:
                EndSemester();
            case 8:
                system("cls");
                pStudent->viewProfile_Staff();
                break;
            case 7:
                pHeadClass->showingList();
                break;
            case 6:
                system("cls");
                pHeadClass->viewStudentList();
                break;
            case 5:
                while (true)
                {
                    system("cls");
                    if (curSemester->viewCourse())
                        curCourse->showInfo();
                    else
                        break;
                }
                break;
            case 4:
                while (true)
                {
                    system("cls");
                    if (curSemester->viewCourse())
                        curCourse->showingStudentList(); //Check sau
                    else
                        break;
                }
                break;
            case 2:
                system("cls");
                drawHeader();
                changePassword();
                break;
            case 1:
                flag = 1;
                break;
            case 0:
                delete[] content;
                exitProgram();
            }
        } while (!flag);

        delete[] content;
        choice = 1;

    } while (choice);
}

void EndSemesterMenu() {
    SetColor(7, 1);

    std::cout << "\n"; gotox(mid - 74 / 2 + 15);
    std::cout << "State: End of Semester.";

    std::cout << "\n"; gotox(mid - 74 / 2 + 15);
    std::cout << "Current Year:";
    std::cout << curSchoolYear->year;

    std::cout << "\n"; gotox(mid - 74 / 2 + 15);
    std::cout << "Current Semester: ";
    std::cout << curSemester->getSem();
    
    SetColor(7, 0);
    drawBox(mid - 53 / 2, 11, 53, 19);
    gotoxy(mid - 13 / 2, 12);
    std::cout << "MENU OPTIONS\n";

    drawLine(53, mid - 53 / 2);

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "1. Export list of students in a course to CSV";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "2. Import scoreboard of a course";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "3. View the scoreboard of a course";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "4. Update a student's result";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "5. View the scoreboard of a class";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "6. End ?\n";

    drawLine(53, mid - 53 / 2);

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "7. View student profile";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "8. View a list of classes";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "9. View a list of student in a class";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "10. View a list of courses";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "11. View a list of students in a course\n";

    drawLine(53, mid - 53 / 2);
    
    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "12. Change Password";

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "0. Exit";
}

void EndSemester() {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);

    // Move console window to center of the screen
    system("mode con: cols=156 lines=80");
    MoveWindow(console, (GetSystemMetrics(SM_CXSCREEN) - r.right) / 2, (GetSystemMetrics(SM_CYSCREEN) - r.bottom) / 2, r.right, r.bottom, TRUE);
    int option;
    std::ifstream fin;
    std::ofstream fout;
    std::string* content = new std::string[15];

    content[0] = "1. Export list of students in a course to CSV";
    content[1] = "2. Import scoreboard of a course";
    content[2] = "3. View the scoreboard of a course";
    content[3] = "4. Update a student's result";
    content[4] = "5. View the scoreboard of a class";
    content[5] = "6. End ?";
    content[6] = "-";
    content[7] = "7. View student profile";
    content[8] = "8. View a list of classes";
    content[9] = "9. View a list of student in a class";
    content[10] = "10. View a list of courses";
    content[11] = "11. View a list of students in a course";
    content[12] = "-";
    content[13] = "12. Change Password";;
    content[14] = "0. Exit";
    curSemester->loadCourse();
    do {
        system("cls");
        drawHeader();
        EndSemesterMenu();
        option = movingBar(mid - 51 / 2, 14, 14, mid + 51 / 2, 28, 1, content);

        switch (option) {
        case 14:
            system("cls");
            curSemester->viewCourse();
            curCourse->ExportClass();
            break;
        case 13:
            system("cls");
            curCourse->ImportScoreboard();
            break;
        case 12:
            system("cls");
            while (true)
            {
                system("cls");
                if (curSemester->viewCourse())
                    curCourse->ViewScoreboard();
                else
                    break;
            }
            break;
        case 11:
            system("cls");
            while (true)
            {
                system("cls");
                if (curSemester->viewCourse())
                    curCourse->updateStudentResult();
                else
                    break;
            }
            break;
        case 10:
            system("cls");
            //view the class
            pHeadClass->getClass();

            curClass->showScoreBoardOfClass();

            break;
        case 7:
            system("cls");
            pStudent->viewProfile_Staff();
            break;
        case 6:
            pHeadClass->showingList();
            break;
        case 5:
            system("cls");
            pHeadClass->viewStudentList();
            break;
        case 4:
            while (true)
            {
                system("cls");
                if (curSemester->viewCourse())
                    curCourse->showInfo();
                else
                    break;
            }
            break;
        case 3:
            while (true)
            {
                system("cls");
                if (curSemester->viewCourse())
                    curCourse->showStudent(); //Check sau
                else
                    break;
            }
            break;
        case 1:
            system("cls");
            drawHeader();
            changePassword();
            break;
        case 0:
            delete[] content;
            exitProgram();
        default:
            std::cout << "\n\t\t Invalid input.";
        }
    } while (option != 0);
}



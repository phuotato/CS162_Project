#include "Universal.h"
#include "SchoolYear.h"
#include "Student.h"
#include "Date.h"
#include "Course.h"
#include "Graphic.h"
#include "Class.h"

//Global variable
extern schoolYear* pHeadSchoolYear;
extern schoolYear* curSchoolYear;
extern Class* pHeadClass;
extern Class* pTailClass;
extern int mid;

//Struct variable
student* pStudent = nullptr;

//I/O command
extern std::ifstream fin;
extern std::ofstream fout;

//Constructor for Class
Class::Class(std::string Name) :Name(Name) {}

//Functions for Class

void Class::LoadFile()
{
    fin.open("../Data/Class/Class.txt");
    while (!fin.eof())
    {
        std::string curName;
        getline(fin, curName);
        if (curName == "")															//Check if the file is empty or not
            return;

        if (!pHeadClass)
        {
            pHeadClass = new Class(curName);
            pTailClass = pHeadClass;
        }
        else
        {
            Class* tmp = new Class(curName);
            pTailClass->pNext = tmp;
            pTailClass = tmp;
        }
    }
}

void Class::addNewClass() {
    bool flag = 0;
    system("cls");

    pHeadClass->LoadFile();
    SetColor(7, 9);
    gotoxy(mid - 24 / 2, 2);
    std::cout << "Current year: " << curSchoolYear->getYear() << std::endl;
    SetColor(7, 0);
    showClassList();

    while (true) {

        //Enter the class code
        std::cout << "\n"; gotox(mid - 56 / 2);
        std::cout << "Please enter the name of the class you want to create: ";
        std::string Name;  std::cin >> Name;
        std::cin.ignore();

        //Check the class
        if (checkExistClass(Name) == 0) {
            std::cout << "\n"; gotox(mid - 29 / 2);
            SetColor(7, 12);
            std::cout << "This class is already exist.";
            SetColor(7, 0);
            return;
        }

        //Check the class if correct to add
        else if (pHeadClass->CheckClasses(Name) == 0) {
            std::cout << "\n"; gotox(mid - 35 / 2);
            SetColor(7, 12);
            std::cout << "Please enter the class correctly.\n";
            SetColor(7, 0);
            return;
        }

        //Add	
        else {
            //Create dummy node and initialize
            if (!pHeadClass) pHeadClass = new Class("");
            pTailClass = pHeadClass;
            Class* tmp = pTailClass;

            //Add the new class
            tmp->pNext = new Class(Name);
            pTailClass = tmp->pNext;
            pTailClass->getName() = Name;
            pTailClass->pNext = nullptr;

            //Delete dummy node
            if (pHeadClass->getName() == "") {
                delete pHeadClass;
                pHeadClass = tmp;
            }

            //Add Class into the text file
            fout.open("../Data/Class/Class.txt", std::ios::app);
            fout << "\n";
            fout << Name;
            fout.close();

            //Create folder for class
            //if (_mkdir(("../Data/Class/" + Name).c_str()));

            //Create CSV file for class
            fout.open("../Data/Class/" + Name + ".csv");

            //Create column
            fout << "No,";
            fout << "Student ID,";
            fout << "Last Name,";
            fout << "First Name,";
            fout << "Gender,";
            fout << "Date of Birth,";
            fout << "Social ID,";

            fout.close();
        }

        loadingPage();
        
        std::cout << "\n\n"; gotox(mid - 20 / 2);
        SetColor(7, 2);
        std::cout << " Create succesfully\n";
        SetColor(7, 0);

        Sleep(2000);
        return;
    }
}

bool Class::checkExistClass(std::string Name)
{
    if (pHeadClass)
    {
        for (Class* cur = pHeadClass; cur; cur = cur->pNext)
        {
            if (cur->getName() == Name)
                return 0;
        }
    }
    return 1;
}

void Class::deleteClass() {
    for (; pHeadClass;)
    {
        Class* tmp = pHeadClass->pNext;
        delete pHeadClass;
        pHeadClass = tmp;

    }
}

bool Class::CheckClasses(std::string curName) {
    int length = curName.length();
    if (length < 4) return 0;

    for (int i = 0; i < 2; i++) {
        if (curName[i] < '0' || curName[i] > '9') return 0;
    }
    if (curName[2] < 'A' && curName[2] > 'Z') return 0;

    for (int i = 3; i < length; i++) {
        if (curName[i] > '0' && curName[i] <= '9') return 1;
    }
    return 0;
}

std::string Class::getName() {
    return Name;
}

void Class::showClassList() {
    if (!pHeadClass) {
        SetColor(7, 12);
        std::cout << "\n"; gotox(mid - 29 / 2);
        std::cout << "There is no class currently.\n";
        SetColor(7, 0);
        return;
    }

    gotox(mid - 46 / 2);
    std::cout << "+-------------------------------------------+\n";
    for (Class* cur = pHeadClass; cur; cur = cur->pNext) {
        gotox(mid - 46 / 2);
        std::cout << "|                                           |";
        gotox(mid - (cur->getName()).length() / 2);
        std::cout << cur->getName() << "\n";
    }

    gotox(mid - 46 / 2);
    std::cout << "+-------------------------------------------+\n";

}

//Function for students
void Class::getOption()
{
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t|              MENU OPTIONS                        |";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t| 1. Add students directly on the screen           |";
    std::cout << "\n\t\t| 2. Add students by inputting a CSV file          |";
    std::cout << "\n\t\t| 0. Exit                                          |";
    std::cout << "\n\t\t+--------------------------------------------------+";
    std::cout << "\n\t\t Enter your choice: ";
    int choice;
    std::cin >> choice;
    bool condition = true;
    while (condition)
    {
        switch (choice){
        case 1: {
            condition = false;
            addStudentto1stClass_Console();
            break;
        }
        case 2: {
            condition = false;
            addStudentto1stClass_File();
            break;
        }
        case 0:
            return;
        default: {
        
            std::cout << "Option Not Found!" << "\n";
            std::cout << "Please input the available option: " << "\n";
        }
        }
    }
}
void Class::addStudentto1stClass_Console()
{
    // find existed students in the CSV file and show'em out
    std::string classname;
    std::cout << "Input the classcode: ";
    std::getline(std::cin, classname);
    Class* curClass = pHeadClass;   // need to load the pHeadClass first before use
    for (curClass; curClass != nullptr; curClass = curClass->pNext)
    {
        if (curClass->Name == classname)
            break;
    }
    if (!curClass)
    {
        std::cout << "Cannot find the class you've entered! Return to menu to add this class to the semester or reenter the available class!" << "\n";
        return;
    }
    char choice = 'Y';
    student* curStudent = curClass->headS;
    while (choice == 'Y' || choice == 'y')
    {
        // get information of that student
        int no;
        std::string id, firstname, lastname, socialId;
        bool gender;
        date dob;
        std::string getNO;
        std::cout << "No: ";
        std::getline(std::cin, getNO);
        no = stoi(getNO);
        std::cout << "Student ID: ";
        std::getline(std::cin, id);
        while (curStudent != nullptr)       // check whether that student ID exists in the student list or not
        {
            if (curStudent->getStudentID() == id)
            {
                std::cout << "This student's already in this class! Please try again." << "\n";
                choice = 'N';
                break;       
            }
            else
                curStudent = curStudent->pNext; 
        }
        if (choice == 'Y' || choice == 'y')
        {
            std::cout << "First name: ";
            std::getline(std::cin, firstname);
            std::cout << "Last name: ";
            std::getline(std::cin, lastname);
            std::cout << "Gender: ";
            std::string getGender;
            std::getline(std::cin, getGender);
            gender = stoi(getGender);
            std::cout << "Date of birth (DDMMYYYY): ";
            std::string getDay, getMonth, getYear;
            std::getline(std::cin, getDay);
            std::getline(std::cin, getMonth);
            std::getline(std::cin, getYear);
            int day = stoi(getDay);
            int month = stoi(getMonth);
            int year = stoi(getYear);
            std::cout << "Social ID: ";
            std::getline(std::cin, socialId);

            // link each student node to the current student list of that class
            student* newStudent = new student(no, id, firstname, lastname, gender, day, month, year, socialId, nullptr);
            curStudent = newStudent;
            curStudent = curStudent->pNext;

            // Save student information to a text file
            if (!curStudent->checkExistFile(id))
                exportNewStudentProfile(classname, id, firstname, lastname, no, gender, day, month, year, socialId);
            // Save the info of that student back to the .csv file
            if (checkClassInfo(classname))
            {
                fout.open("../Data/Class" + classname + ".csv", std::ios::app);
                fout << "Student ID,No,First name,Last name,Gender,Date Of Birth,Social ID" << "\n";
            }
            else
            {
                fout.open("../Data/Class" + classname + ".csv", std::ios::app);
                fout << id << "," << no << "," << firstname << "," << lastname << "," << gender << "," << day << "/" << month << "/" << year << ",'" << socialId << "\n";
            }
        }
        // Option for user
        std::cout << "Enter Y (or y) to continue inputting on console" << "\n";
        std::cout << "Enter N (or N) to stop inputting." << "\n";
        std::cin >> choice;
        curStudent = curClass->headS;       // reset pointer
    }
}
bool Class::checkClassInfo(std::string classcode)
{
    // this function is to check if the class info exists in the Data folder or not
    fin.open("../Data/Class/" + classcode + ".csv");
    if (!fin)   // cannot open
    {
        fin.close();
        return false;
    }
    else
    {
        fin.close();
        return true;
    }
}
void Class::addStudentto1stClass_File()
{
    // user input the link of the file
    std::cout << "Enter the link to the CSV file (Note that the name of the file should be the name of the class that the students belong to): " << "\n";
    std::wcout << "For example: 22TT1.csv means that the students added will belong to the class 22TT1" << "\n";
    std::string fileName;
    std::getline(std::cin, fileName);
    std::ifstream fin(fileName);
    std::string classcode;
    // Find the classcode
    int pos = fileName.rfind('\\');
    classcode = fileName.substr(pos + 1);
    Class* curClass = pHeadClass;
    for (curClass; curClass != nullptr; curClass = curClass->pNext)
    {
        if (curClass->Name == classcode)
        {
            break;
        }
    }
    if (!curClass)
    {
        std::cout << "Cannot find the class you've entered! Return to menu to add this class to the semester or reenter the available class!" << "\n";
        return;
    }
    if (!fin)
    {
        std::cout << "Error loading data! Please try again.";
        return;
    }
    student* curStudent = curClass->headS;
//    loadingPage();
    if (checkClassInfo(classcode))
    {
        std::cout << "This file has been added before!" << "\n";
        return;
    }
    fout.open(".. /Data/Class/" + classcode + ".csv");  // will make a copy of this .csv to the Data folder
    std::string redundant;      // the first line of the csv file 
    std::getline(fin, redundant);   
    fout << redundant << "\n";
    int line = 2;
    bool state = true;
    while (!fin.eof())
    {
        // info of a student
        int no;
        std::string id, firstname, lastname, socialId;
        bool gender;
        date dob;
        std::string getNO;
        std::getline(fin, getNO, ',');
        std::getline(fin, id, ',');
        if (fin.eof())
            break;
        while (curStudent != nullptr)       // check whether that student ID exists in the student list or not
        {
            if (curStudent->getStudentID() == id)
            {
                std::cout << "At line " << line << ", student ID " << id << " already exists in the list" << "\n";
                state = false;
                break;
            }
            else
                curStudent = curStudent->pNext;
        }
        no = stoi(getNO);
        std::getline(fin, firstname, ',');
        std::getline(fin, lastname, ',');
        std::string getGender;
        std::getline(fin, getGender, ',');
        gender = stoi(getGender);
        std::string getDay, getMonth, getYear;
        std::getline(fin, getDay, '/');
        std::getline(fin, getMonth, '/');
        std::getline(fin, getYear, ',');
        int day = stoi(getDay);
        int month = stoi(getMonth);
        int year = stoi(getYear);
        fin.ignore();
        std::getline(fin, socialId);
        // Save student information to a text file
        if (state)
        {
            if (!curStudent->checkExistFile(id))
                exportNewStudentProfile(classcode, id, firstname, lastname, no, gender, day, month, year, socialId);
            student* newStudent = new student(no, id, firstname, lastname, gender, day, month, year, socialId, nullptr);
            curStudent = newStudent;
            curStudent = curStudent->pNext;
            // Save the info of this student to a "copy" file
            fout << id << "," << no << "," << firstname << "," << lastname << "," << gender << "," << day << "/" << month << "/" << year << ",'" << socialId << "\n";
        }
        ++line;                         
        curStudent = curClass->headS;       // reset conditions for the next turn
        state = true;   
    }
    fin.close();
    fout.close();
    system("cls");
    std::cout << "Add students successfully! System will go back to the menu now." << std::endl << std::endl;
    system("pause");
}
bool student::checkExistFile(std::string id)
{
    fin.open("../Data/StudentProfile/" + id + ".txt");
    if (!fin)
    {
        return false;
    }
    else
    {
        fin.close();
        return true;
    }
}
void Class::loadStudent()
{   
    Class* curClass = pHeadClass;
    while (curClass != nullptr)
    {
        std::string className = curClass->Name;
        fin.open("../Data/Class/" + className + ".csv");
        student* curStudent = curClass->headS;
        while (curStudent != nullptr)
        {
            if (!fin)
                break;
            std::string redundant;
            std::getline(fin, redundant);
            int no;
            std::string id, firstname, lastname, socialId;
            bool gender;
            date dob;
            std::string getNO;
            std::getline(fin, getNO, ',');
            std::getline(fin, id, ',');
            if (fin.eof())
                break;
            no = stoi(getNO);
            std::getline(fin, firstname, ',');
            std::getline(fin, lastname, ',');
            std::string getGender;
            std::getline(fin, getGender, ',');
            gender = stoi(getGender);
            std::string getDay, getMonth, getYear;
            std::getline(fin, getDay, '/');
            std::getline(fin, getMonth, '/');
            std::getline(fin, getYear, ',');
            int day = stoi(getDay);
            int month = stoi(getMonth);
            int year = stoi(getYear);
            fin.ignore();
            std::getline(fin, socialId);
            student* newStudent = new student(no, id, firstname, lastname, gender, day, month, year, socialId, nullptr);
            curStudent = newStudent;
            curStudent = curStudent->pNext;
        }
        curClass = curClass->pNext;
        fin.close();
    }
}
void Class::exportNewStudentProfile(std::string classcode, std::string id, std::string firstname, std::string lastname, int no, bool gender, int day, int month, int year, std::string socialID)
{

    fout.open("../Data/StudentProfile/" + id + ".txt");
    fout << id << "\n";
    fout << no << "\n";
    fout << firstname << "\n";
    fout << lastname << "\n";
    fout << day << " " << month << " " << year << "\n";
    fout << gender << "\n";
    fout << socialID;
    fout.close();

}
void student::viewProfile()
{
    char opt = 'Y';
    while (opt == 'Y' || opt == 'y')
    {
        std::string username;
        std::cout << "Input the student ID: ";
        std::cin.ignore();
        std::getline(std::cin, username);
        if (!checkExistFile(id))
        {
            std::cout << "The information of this student isn't available right now. Please complete their information to see later" << "\n";
            std::cout << "Please input another ID! " << "\n";
            continue;
        }
        fin.open("../Data/StudentProfile/" + username + ".txt");
        std::string id, firstname, lastname, socialId;
        std::getline(fin, id);
        std::string getNO;
        std::getline(fin, getNO);
        std::getline(fin, firstname);
        std::getline(fin, lastname);
        std::string getDay, getMonth, getYear;
        std::getline(fin, getDay, ' ');
        std::getline(fin, getMonth, ' ');
        std::getline(fin, getYear);
        std::string getGender;
        std::getline(fin, getGender);
        std::getline(fin, socialId);
        fin.close();
        std::cout << "No: " << getNO << "\n";
        std::cout << "Student ID: " << id << "\n";
        std::cout << "Name: " << firstname << " " << lastname << "\n";
        std::cout << "Gender: ";
        if (getGender == "0")
            std::cout << "Male" << "\n";
        else
            std::cout << "Female" << "\n";
        std::cout << "Date of birth: " << getDay << "/" << getMonth << "/" << getYear << "\n";
        std::cout << "Social ID: " << socialId << "\n";
        std::cout << "Would you like to view other information of another student?" << "\n";
        std::cout << "Enter Y (or y) to continue viewing." << "\n";
        std::cout << "Enter N (or N) to stop." << "\n";
        std::cin >> opt;
    }

    std::cout << std::endl;
    std::cout << "Process done! The system will go back to the menu." << std::endl;
    system("pause");
}
void Class::sortStudentsLexicographically(std::string classcode)
{
    Class* curClass = pHeadClass;
    if (!curClass)
        return;
    student* curStudent = curClass->headS;
    if (!curStudent)
        return;
    student* sortedList = nullptr;
    while (curStudent != nullptr)
    {
        student* nextS = curStudent->pNext;
        if (sortedList == nullptr || stoi(sortedList->getStudentID().substr(5)) > stoi(curStudent->getStudentID().substr(5)))
        {
            curStudent->pNext = sortedList;
            sortedList = curStudent;
        }
        else
        {
            student* current = sortedList;
            while (current->pNext != nullptr && stoi(current->pNext->getStudentID().substr(5)) < stoi(curStudent->getStudentID().substr(5)))
            {
                current = current->pNext;
            }
            curStudent->pNext = current->pNext;
            current->pNext = curStudent;
        }
        curStudent = nextS;
    }
    curClass->headS = sortedList;
}
void Class::deleteStudentList()
{
    Class* curClass = pHeadClass;
    while (curClass != nullptr)
    {
        student* curStudent = curClass->headS;
        while (curStudent != nullptr)
        {
            student* temp = curStudent;
            curStudent = curStudent->pNext;
            delete temp;
        }
        curClass = curClass->pNext;
    }
}

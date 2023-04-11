#include "Universal.h"
#include "SchoolYear.h"
#include "Student.h"
#include "Date.h"
#include "Course.h"
#include "Graphic.h"
#include "Class.h"

//Global variable
extern schoolYear* pHeadSchoolYear;
extern Class* pHeadClass;
extern Class* pTailClass;

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
    while (true) {

        //Enter the class code
        std::cout << "Please enter the name of the class you want to create: ";
        std::string Name;  std::cin >> Name;
        std::cin.ignore();

        //Check the class
        pHeadClass->LoadFile();
        if (checkExistClass(Name) == 0) {
            std::cout << "This class is already exist.\n";
            return;
        }

        //Check the class if correct to add
        else if (pHeadClass->CheckClasses(Name) == 0) {
            std::cout << "Please enter the class correctly.\n";
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
            fout << "Student ID,";
            fout << "No,";
            fout << "First Name,";
            fout << "Last Name,";
            fout << "Gender,";
            fout << "Date of Birth,";
            fout << "Social ID,";

            fout.close();
        }

        loadingPage();
        system("cls");
        std::cout << "Create succesfully\n";
        return;
    }
}

void Class::createInformationClass() {
    fin.open(".. /Data/Class/Class.txt");

    while (true) {

        if (!fin) return;
        std::string ClassName;													//Read in class
        getline(fin, ClassName, ' ');
        fin.ignore();

        if (!pHeadClass) pHeadClass = new Class("");
        Class* tmp = pHeadClass;
        tmp->pNext = new Class(ClassName);

        pTailClass = tmp;
        if (pHeadClass->getName() == "") delete pHeadClass;

    }

    fin.close();
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

void Class::Choices() {
    system("cls");
    int k;
    do {
        std::cout << "\n\t\t+--------------------------------------------------+";
        std::cout << "\n\t\t|              MENU OPTIONS                        |";
        std::cout << "\n\t\t+--------------------------------------------------+";
        std::cout << "\n\t\t| 1. Load all classes in all school year           |";
        std::cout << "\n\t\t| 2. Add more class                                |";
        std::cout << "\n\t\t| 0. Exit                                          |";
        std::cout << "\n\t\t+--------------------------------------------------+";
        std::cout << "\n\t\t Enter your choice: ";
        std::cin >> k;
        if (k == 0) break;
        switch (k) {
        case 1:
            pHeadClass->createInformationClass();
            break;
        case 2:
            pHeadClass->addNewClass();
            break;
        default:
            std::cout << "You have entered wrong! Try again.\n";
            break;
        }
        Sleep(1000);
        system("cls");
    } while (k != 0);
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


/*void Class::getOption()
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
    // from the classcode -> find the corresponding schoolyear
    std::cout << "Enter the class code (Example: 22TT2, 22TT1, 21CLC06, 20VP,...):  ";
    std::string classcode;
    std::cin.ignore();
    std::getline(std::cin, classcode);
    std::string year = classcode.substr(0, 2);
    int temp = stoi(year) + 1;
    std::string schoolyear = "20" + year + "-" + "20" + std::to_string(temp); 

    

    char choice = 'N';
    while (choice == 'N' || choice == 'n')
    {
        // get information of that student
        int no;
        std::string id, firstname, lastname, socialId;
        bool gender;
        date dob;
        std::cout << "Student: ";
        std::getline(std::cin, id);
        std::string getNO;
        std::cout << "No: ";
        std::getline(std::cin, getNO);
        no = stoi(getNO);
        std::cout << "First name: ";
        std::getline(std::cin, firstname);
        std::cout << "Last name: ";
        std::getline(std::cin, lastname);
        std::cout << "Gender: ";
        std::string getGender;
        std::getline(std::cin, getGender);
        gender = stoi(getGender);
        std::cout << "Date of birth (DD/MM/YYYY): ";
        std::string getDay, getMonth, getYear;
        std::getline(std::cin, getDay);
        std::getline(std::cin, getMonth);
        std::getline(std::cin, getYear);
        int day = stoi(getDay);
        int month = stoi(getMonth);
        int year = stoi(getYear);
        std::getline(std::cin, socialId);
        student* newStudent = new student(no, id, firstname, lastname, gender, day, month, year, socialId, nullptr);
        newStudent->pNext = pHeadSchoolYear->pHeadClass->headS; // cannot access the year of pHeadSchoolYear!
        headS = newStudent;
        std::cout << "Would you like to quick inputting students by using a CSV file?" << "\n";
        std::cout << "Enter Y (or y) to quick inputting students by using a CSV file." << "\n";
        std::cout << "Enter N (or n) to continue inputting on console" << "\n";
        std::cout << "Enter 0 to stop inputting." << "\n";
        std::cin >> choice;
        std::cin.ignore();
        
        if (choice == 'Y' || choice == 'y')
        {
            addStudentto1stClass_File();
        }
    }
}
void Class::addStudentto1stClass_File()
{
    std::cout << "Enter your class code (Example: 22TT2, 22TT1, 21CLC06, 20VP,...):  ";
    std::string classcode;
    std::getline(std::cin, classcode);
    std::ifstream fin("../StudentProfile/" + classcode + ".csv");
    loadingPage();
    if (!fin)
    {
        system("cls");
        std::cout << "Error loading data! Please try again.";
        return;
    }
    std::string redundant;
    std::getline(fin, redundant);
    while (!fin.eof())
    {
        int no;
        std::string id, firstname, lastname, socialId;
        bool gender;
        date dob;
        std::getline(fin, id, ',');
        std::string getNO;
        std::getline(fin, getNO, ',');
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
        newStudent->pNext = headS;
        headS = newStudent;
    }
    system("cls");
    std::cout << "Add students successfully! System will go back to the menu now." << std::endl << std::endl;
    system("pause");
}
*/
void student::viewProfile(student*& headS)
{
    student* temp = headS;
    std::string username;
    std::cout << "Input the student ID: ";
    std::cin.ignore();
    std::getline(std::cin, username);
    if (!headS)
    {
        std::cout << "No information currently! Please load the data first." << std::endl << std::endl;
        std::cout << "Process done! The system will go back to the menu." << std::endl;
        system("pause");
        return;
    }
    while (temp != nullptr)
    {
        if (temp->id == username)
        {
            std::cout << "Student ID: " << temp->id << std::endl;
            std::cout << "No: " << temp->no << std::endl;
            std::cout << "Name: " << temp->firstName << " " << temp->lastName << std::endl;
            std::cout << "Date of birth: " << temp->dob.getDay() << "/" << temp->dob.getMonth() << "/" << temp->dob.getYear() << std::endl;            std::cout << "Gender: ";
            if (temp->gender == 0)
                std::cout << "Male";
            else
                std::cout << "Female";
            std::cout << std::endl;
            std::cout << "Social ID: " << temp->socialId << std::endl;
            break;
        }
        else
            temp = temp->pNext;
    }
    if (temp == nullptr)
        std::cout << "No information about this student!" << std::endl;
    std::cout << std::endl;
    std::cout << "Process done! The system will go back to the menu." << std::endl;
    system("pause");
}

void student::deleteStudentList(student*& headS)
{
    student* cur = headS;
    while (cur != nullptr)
    {
        student* temp = cur;
        cur = cur->pNext;
        delete temp;
    }
}

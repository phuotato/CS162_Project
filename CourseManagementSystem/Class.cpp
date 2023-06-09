﻿#include "Universal.h"
#include "SchoolYear.h"
#include "Student.h"
#include "Date.h"
#include "Course.h"
#include "Graphic.h"
#include "Class.h"
#include "Display.h"

//Global variable
extern schoolYear* pHeadSchoolYear;
extern schoolYear* curSchoolYear;
extern schoolYear* pTailSchoolYear;
extern Class* pHeadClass;
extern Class* curClass;
extern Class* pTailClass;
extern semester* curSemester;
extern int mid;


//Struct variable
student* pStudent = nullptr;

//I/O command

//Constructor for Class
Class::Class(std::string Name) :Name(Name) {}

//Functions for Class

void Class::LoadFile()
{
    if (pHeadClass) return; //if there is a LL, don't load
    std::ifstream fin("../Data/Class/Class.txt");
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
    fin.close();
}

void Class::addNewClass() {
    bool flag = 0;
    system("cls");
    std::string year = curSchoolYear->getYear();
    //Delete Class that not in that year
    //Create dummy
    Class* tmp = pHeadClass;
    pHeadClass = new Class("Test");
    pHeadClass->pNext = tmp;

    for (curClass = pHeadClass; curClass && curClass->pNext;) {
        if (curClass->pNext->getName()[0] != year[2] || curClass->pNext->getName()[1] != year[3]) {
            tmp = curClass->pNext->pNext;
            delete curClass->pNext;
            curClass->pNext = tmp;
        }
        else if (curClass->pNext->pNext) curClass = curClass->pNext;
        else break;
    }
    //Delete dummy
    tmp = pHeadClass->pNext;
    delete pHeadClass;
    pHeadClass = tmp;
    tmp = nullptr;
    curClass = pHeadClass;

    std::ofstream fout;
    while (true) {
        system("cls");

        //Display pages
        if (curClass != nullptr) showingList();
        else {
            drawHeader();
            std::cout << "\n"; gotox(mid - 29/2);
            SetColor(7, 4); std::cout << "There is no class currently!"; SetColor(7, 0);
        }

        //Enter the class code
        std::cout << "\n"; gotox(mid - 62 / 2);
        std::cout << "Please make sure to input valid class (Ex:" << year[2] << year[3] << " from " << year << ")";

        std::cout << "\n"; gotox(mid - 62 / 2);
        std::cout << "Please enter the name of the class you want to create";

        std::cout << "\n"; gotox(mid - 62 / 2);
        std::cout << "Press enter to stop: ";
        std::string Name;  getline(std::cin, Name);

        //if enter then return
        if (Name == "") return;

        //Check the class
        if (checkExistClass(Name) == 0) {
            std::cout << "\n"; gotox(mid - 29 / 2);
            SetColor(7, 12);
            std::cout << "This class is already exist.";
            SetColor(7, 0);

            Sleep(2000);
            continue;
        }

        //Check the class if correct to add
        else if (pHeadClass->CheckClasses(Name) == 0) {
            std::cout << "\n"; gotox(mid - 35 / 2);
            SetColor(7, 12);
            std::cout << "Please enter the class correctly.\n";
            SetColor(7, 0);

            Sleep(2000);
            continue;
        }


        //Check if this class is in current year
        else if (year[2] != Name[0] || year[3] != Name[1]) {
            std::cout << "\n"; gotox(mid - 29 / 2);
            SetColor(7, 12);
            std::cout << "This class is not in this year.";
            SetColor(7, 0);

            Sleep(2000);
            continue;
        }

        //Add	
        else {
            //Create dummy node and initialize
            if (!pHeadClass) {
                pHeadClass = new Class("");
                pTailClass = pHeadClass;
            }

            //Add the new class
            pTailClass->pNext = new Class(Name);
            pTailClass->pNext->pNext = nullptr;
            curClass = pTailClass;

            //Delete dummy node
            if (pHeadClass->getName() == "") {
                tmp = pHeadClass->pNext;
                delete pHeadClass;
                pHeadClass = tmp;
            }

            //Add Class into the text file
            fout.open("../Data/Class/Class.txt", std::ios::app);
            fout << "\n";
            fout << Name;
            fout.close();

            //Create CSV file for class
            fout.open("../Data/Class/" + Name + ".csv");

            //Create column
            fout << "No,";
            fout << "Student ID,";
            fout << "Last Name,";
            fout << "First Name,";
            fout << "Gender,";
            fout << "Date of Birth,";
            fout << "Social ID" << "\n";

            fout.close();

            //Add Class into the text file
            fout.open("../Data/SchoolYear/" + curSchoolYear->year + "../" + "Class/Class.txt", std::ios::app);
            fout << "\n";
            fout << Name;
            fout.close();

            //Create CSV file for class
            fout.open("../Data/Class/" + Name + ".csv");

            //Create column
            fout << "No,";
            fout << "Student ID,";
            fout << "Last Name,";
            fout << "First Name,";
            fout << "Gender,";
            fout << "Date of Birth,";
            fout << "Social ID" << "\n";

            fout.close();
        }

        loadingPage();
        
        std::cout << "\n\n"; gotox(mid - 20 / 2);
        SetColor(7, 2);
        std::cout << " Create succesfully\n";
        SetColor(7, 0);

        Sleep(500);
        return;
    }
}

bool Class::checkLatestYear() {
    if (curSchoolYear->getYear() != pTailSchoolYear->getYear()) {
        gotoxy(mid - 44 / 2, 26);
        SetColor(7, 12);
        std::cout << "Sorry! You can't add to old school year.";
        SetColor(7, 0);

        Sleep(1000);
        return 0;
    }
    else return 1;
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
    Class* current = pHeadClass;
    while (current) {
        Class* next = current->pNext;
        delete current;
        current = next;
    }
    pHeadClass = nullptr;
    pTailClass = nullptr;
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

void Class::showClassList(short range, short& Pcur) {
    if (!pHeadClass) {
        SetColor(7, 12);
        std::cout << "\n"; gotox(mid - 29 / 2);
        std::cout << "There is no class currently.\n";
        SetColor(7, 0);
        return;
    }

    short i = 5;
    short k = 0;

    gotoy(5);
    for (; curClass && k < range; curClass = curClass->pNext, i++, k++) {
        gotox(mid - ((curClass->getName()).length()) / 2);
        std::cout << curClass->getName() << "\n";
        Pcur++;
    }
    drawBox(mid - 46 / 2, 4, 46, k + 4);

    gotoy(-2);
    drawLine(46, mid - 46 / 2);
    std::cout << "\n\n"; gotox(mid - 46 / 2);
}

// Show classP
void Class::showP(short range, short& Pcur) {
    curClass = pHeadClass;

    //Check if the last page
    if (Pcur % range == 0) {
        for (int i = 0; i < Pcur - range * 2; i++) curClass = curClass->pNext;
        Pcur -= range * 2;
    }
    else {
        for (int i = 0; i < Pcur - (Pcur % range) - range; i++) curClass = curClass->pNext;
        Pcur += -(Pcur % range) - range;
    }
}

//Get all class
int Class::getAllClass() {
    int i = 0;
    for (Class* cur = pHeadClass; cur; cur = cur->pNext, i++);
    return --i;
}

void Class::showingList() {
    std::string displayk = "N";
    std::string* content = nullptr;
    bool EnterConfirm = 0;
    int yp = 6;
    short TH = 3;
    short range = 5;
    short Pcur = 0;
    int APages = getAllClass() / range + 1;
    curClass = pHeadClass;

    system("cls");
    while (true) {

        switch (TH) {
        //Next page
        case 3: {
            if (curClass == nullptr) {
                SetColor(7, 12);
                if (Pcur % range == 0 && Pcur != 0) gotoxy(mid - 25 / 2, range + 8);
                else gotoxy(mid - 25 / 2, Pcur % range + 8);
                std::cout << "You are at the last page";
                SetColor(7, 0);

                Sleep(1000);

                //Reset the command
                gotox(mid - 47 / 2);
                std::cout << "                                                          \r";

            }
            else {
                system("cls");
                drawBox(15, 2, 30, 23);
                Tutorial(content);
                showClassList(range, Pcur);
                Description(range, APages, (Pcur - 1) / range + 1, Pcur, mid - 45 / 2, 46);
            }
            yp = 6;
            break;
        }
              //Previous Page
        case 2: {
            if (Pcur <= range) {
                SetColor(7, 12);
                if (Pcur % range == 0 && Pcur != 0) gotoxy(mid - 25 / 2, range + 8);
                else gotoxy(mid - 25 / 2, Pcur % range + 8);
                std::cout << "You are at the first page";
                SetColor(7, 0);

                Sleep(2000);

                //Reset the command
                gotox(mid - 47 / 2);
                std::cout << "                                                          \r";

            }
            else {
                system("cls");
                drawBox(15, 2, 30, 23);
                Tutorial(content);
                showP(range, Pcur);
                showClassList(range, Pcur);
                Description(range, APages, (Pcur - 1) / range + 1, Pcur, mid - 45 / 2, 46);
            }
            yp = 6 + 4;
            break;
        }
              //Enter to confirm
        case 0: {
            EnterConfirm = 1;
            break;
        }
              //Change list
        case 1: {

            if (Pcur % range == 0 && Pcur != 0) gotoxy(mid - 50 / 2, range + 8);
            else gotoxy(mid - 50 / 2, Pcur % range + 8);
            std::cout << "Please enter the number you want to change list: ";
            getline(std::cin, displayk);

            if (displayk[0] <= '9' && displayk[0] >= '0') {
                int sample = stoi(displayk);
                if (sample > 10 || sample < 5) {
                    SetColor(7, 12);
                    std::cout << "\n\n"; gotox(mid - 42 / 2);
                    std::cout << "The range is too big or too small (5~10)!";
                    SetColor(7, 0);

                    Sleep(2000);

                    //Reset the command
                    gotox(mid - 47 / 2);
                    std::cout << "                                                          \r";
                    gotoxy(mid - 50 / 2, -3); std::cout << "                                                    ";
                }
                else {
                    //Reset everything
                    range = sample;
                    Pcur = 0;
                    curClass = pHeadClass;
                    APages = getAllClass() / range + 1;

                    //Draw again
                    system("cls");
                    drawBox(15, 2, 30, 23);
                    Tutorial(content);
                    showClassList(range, Pcur);
                    Description(range, APages, (Pcur - 1) / range + 1, Pcur, mid - 45 / 2, 46);
                }
            }
            yp = 6 + 8;
            break;
        }
        }
        if (EnterConfirm == 1) {
            if (Pcur % range == 0 && Pcur != 0) gotoy(range + 8);
            else gotoy(Pcur % range + 8);
            break;
        }
        TH = movingBarTutorial(16, 6, yp, 44, 18, 4, content);
    }
}

//Function for students
void Class::getOption()
{   
    int choice = 0;
    bool condition = true;
    std::string* content = new std::string[3];
    content[0] = "1. Add students directly on the screen";
    content[1] = "2. Add students by inputting a CSV file";
    content[2] = "0. Exit";
    drawBox(mid - 53 / 2, 6, 53, 7);

    gotoxy(mid-13/2, -5);
    std::cout << "MENU OPTIONS\n";

    drawLine(53, mid - 53 / 2);

    std::cout << "\n"; gotox(mid - 49 / 2);
    std::cout << "1. Add students directly on the screen\n";

    gotox(mid - 49 / 2); std::cout << "2. Add students by inputting a CSV file\n";
    gotox(mid - 49 / 2); std::cout << "0. Exit\n\n";

    while (condition)
    {
        choice = movingBar(mid - 51 / 2, 9, 9 + choice, mid + 53 / 2, 11, 1, content);
        switch (choice){
        case 2: {
            condition = false;
            gotoxy(mid - 49 / 2, 13);
            addStudentto1stClass_Console();
            break;
        }
        case 1: {
            condition = false;
            addStudentto1stClass_File();
            break;
        }
        case 0:
            return;
        }
    }
}

bool checkValidName(std::string name)
{
    if (name[0] == ' ')
        return false;
    for (int i = 0; i < name.length(); ++i)
    {
        if (!(name[i] >= 'a' && name[i] <= 'z' || name[i] >= 'A' && name[i] <= 'Z' || name[i] == ' '))
        {
            return false;
        }
    }
    return true;
}
bool checkValidNum(std::string num)
{
    for (int i = 0; i < num.length(); ++i)
    {
        if (!(num[i] >= '0' && num[i] <= '9'))
            return false;
    }
    return true;
}
void Class::addStudentto1stClass_Console()
{
    std::string classname;
    std::cout << "Input the classcode (Press enter to go back): ";
    
    std::getline(std::cin, classname);

    if (classname == "") return;

    Class* curClass = pHeadClass;   // need to load the pHeadClass first before use
    for (curClass; curClass != nullptr; curClass = curClass->pNext)
    {
        if (curClass->Name == classname)
            break;
    }
    if (!curClass)
    {
        std::cout << "\n\n"; gotox(mid - 119 / 2);
        SetColor(7, 4);
        std::cout << "Cannot find the class you've entered! Return to menu to add this class to the semester or reenter the available class!" << "\n";
        SetColor(7, 0);

        Sleep(2000);
        return;
    }

    int choice = 1;
    student* curStudent = curClass->headS;
    student* tail = nullptr;
    while (choice == 1)
    {
        system("cls");
        drawHeader();
        std::cout << "\n\n"; gotox(mid - 49 / 2);
        // get information of that student
        SetColor(7, 9);
        std::cout << "Input the following information of the student: \n";
        SetColor(7, 0);
        int no;
        std::string id, firstname, lastname, socialId;
        int gender;
        date dob;
        std::string getNO;

        gotox(mid - 36 / 2);
        std::cout << "No: ";
        std::getline(std::cin, getNO);
        while (!checkValidNum(getNO))           // check if valid number
        {
            gotox(mid - 36 / 2);
            std::cout << "Invalid input! Please try again! \n";
            gotox(mid - 36 / 2);
            std::cout << "No: ";
            std::getline(std::cin, getNO);
        }
        no = stoi(getNO);

        gotox(mid - 36 / 2);
        std::cout << "Student ID: ";
        std::getline(std::cin, id);
        while (curStudent != nullptr)       // check whether that student ID exists in the student list or not
        {
            if (curStudent->getStudentID() == id)
            {
                std::cout << "\n\n"; gotox(mid - 56 / 2);
                SetColor(7, 4);
                std::cout << "This student's already in this class! Please try again.\n";
                SetColor(7, 0);
                choice = 'N';
                break;       
            }
            if (curStudent->pNext == nullptr)
                tail = curStudent;
            curStudent = curStudent->pNext;
        }

        if (choice == 1)
        {
            gotox(mid - 36 / 2);
            std::cout << "First name: ";
            std::getline(std::cin, firstname);
            while (!checkValidName(firstname))
            {
                gotox(mid - 36 / 2);
                std::cout << "Invalid input! Please try again!\n";
                gotox(mid - 36 / 2);
                std::cout << "First name: ";
                std::getline(std::cin, firstname);
            }
            

            gotox(mid - 36 / 2);
            std::cout << "Last name: ";
            std::getline(std::cin, lastname);
            while (!checkValidName(lastname))
            {
                gotox(mid - 36 / 2);
                std::cout << "Invalid input! Please try again!\n";
                gotox(mid - 36 / 2);
                std::cout << "Last name: ";
                std::getline(std::cin, lastname);
            }

            gotox(mid - 36 / 2);
            std::cout << "Gender (Male: 0 | Female: 1): ";
            std::string getGender;
            std::getline(std::cin, getGender);
            while (!checkValidNum(getGender))
            {
                gotox(mid - 36 / 2);
                std::cout << "Invalid input! Please try again! \n";
                gotox(mid - 36 / 2);
                std::cout << "Gender (Male: 0 | Female: 1): ";
                std::getline(std::cin, getGender);
            }
            gender = stoi(getGender);
            while (gender < 0 || gender > 1)
            {
                gotox(mid - 46 / 2);
                SetColor(7, 4);
                std::cout << "Invalid gender! Please input the correct one!";
                SetColor(7, 0);
                Sleep(1000);

                //Reset
                gotox(mid - 46 / 2); std::cout << "                                             ";
                gotoxy(mid + 24 / 2, -1); std::cout << "         ";
                gotox(mid + 24 / 2);
                std::getline(std::cin, getGender);
                gender = stoi(getGender);
            }

            gotox(mid - 36 / 2);
            std::cout << "Date of birth (DDMMYYYY - For example: 01012004): ";
            std::string getDay, getMonth, getYear;
            std::string getDOB;
            std::getline(std::cin, getDOB);
            while (getDOB.length() != 8)        // check exact 8 digits
            {
                gotox(mid - 36 / 2);
                std::cout << "Invalid input! Please try again! \n";
                gotox(mid - 36 / 2);
                std::cout << "Date of birth (DDMMYYYY - For example: 01012004): ";
                std::getline(std::cin, getDOB);
            }
            getDay = getDOB.substr(0, 2);
            getMonth = getDOB.substr(2, 2);
            getYear = getDOB.substr(4);
            int day = stoi(getDay);
            int month = stoi(getMonth);
            int year = stoi(getYear);
            while (!checkValidDate(day, month, year))
            {
                gotox(mid - 46 / 2);
                SetColor(7, 4);
                std::cout << "Invalid Date! Please input the correct one!";
                SetColor(7, 0);
                Sleep(1000);

                //Reset
                gotox(mid - 46 / 2); std::cout << "                                             ";
                gotoxy(mid + 54 / 2, -1); std::cout << "         ";
                gotox(mid + 54 / 2);

                std::string getDay, getMonth, getYear;
                std::string getDOB;
                std::getline(std::cin, getDOB);
                getDay = getDOB.substr(0, 2);
                getMonth = getDOB.substr(2, 2);
                getYear = getDOB.substr(4);
                day = stoi(getDay);
                month = stoi(getMonth);
                year = stoi(getYear);
            }

            gotox(mid - 36 / 2);
            std::cout << "Social ID: ";
            std::getline(std::cin, socialId);
            while (socialId.length() != 12)
            {
                gotox(mid - 36 / 2);
                SetColor(7, 4); std::cout << "Invalid social ID! Social ID should have exactly 12 digits!"; SetColor(7, 0);
                Sleep(1000);

                //Reset
                gotox(mid - 36 / 2);
                std::cout << "                                                           ";
                gotoxy(mid - 14 / 2, -1); std::cout << "           ";
                gotox(mid - 14 / 2);

                std::getline(std::cin, socialId);
            }

            // link each student node to the current student list of that class
            student* newStudent = new student(no, id, firstname, lastname, gender, day, month, year, socialId, nullptr);
            if (curClass->headS == nullptr)
            {
                curClass->headS = newStudent;
                curStudent = curClass->headS;
            }
            else
            {
                tail->pNext = newStudent;
                tail = tail->pNext;
            }

            // Save student information to a text file
            if (!curStudent->checkExistFile(id))
                exportNewStudentProfile(classname, id, firstname, lastname, no, gender, day, month, year, socialId);
            // Save the info of that student back to the .csv file
            if (!checkClassInfo(classname))
            {
                std::ofstream write("../Data/Class/" + classname + ".csv", std::ios::app);
                write << "Student ID,No,First name,Last name,Gender,Date Of Birth,Social ID" << "\n";
                write.close();
            }
            else
            {
                std::ofstream write("../Data/Class/" + classname + ".csv", std::ios::app);
                write << no << "," << id << "," << firstname << "," << lastname << "," << gender << "," << day << "/" << month << "/" << year << ",'" << socialId << "\n";
                write.close();
            }

            //Loading
            std::cout << "\n\n"; gotox(mid - 48 / 2);
            loadingPage();
            gotox(mid - 27 / 2); std::cout << "                            ";
            gotoxy(mid - 10 / 2, -2); std::cout << "         ";
            SetColor(7, 2);
            gotox(mid - 20 / 2);
            std::cout << "Added Succesfully";
            SetColor(7, 0);
            Sleep(1000);

            gotox(mid - 20 / 2); std::cout << "                   ";

        }
        // Option for user

        gotoxy(mid - 37 / 2, 20); std::cout << "Do you want to add more student?";
        choice = YNQuestions(mid - 40 / 2, 19, 40);

        curStudent = curClass->headS;       // reset pointer
    }
}
bool Class::checkClassInfo(std::string classcode)
{
    // this function is to check if the class info exists in the Data folder or not
    std::ifstream read;
    read.open("../Data/Class/" + classcode + ".csv");
    if (!read)   // cannot open
    {
        read.close();
        return false;
    }
    else
    {
        read.close();
        return true;
    }
}
void Class::addStudentto1stClass_File()
{
    // this function is for updating the class

    // user input the link of the file
    system("cls");
    drawHeader();
    gotox(mid - 86/2);
    std::cout << "For example: 22TT1.csv means that the students added will belong to the class 22TT1\n\n";

    gotox(mid - 60 / 2);
    std::cout << "Input the link here: ";
    std::string fileName;
    std::string directory;
    std::getline(std::cin, directory);
    std::ifstream read(directory);
    if (!read)
    {
        std::cout << "\n\n"; gotox(mid - 38/2);
        SetColor(7, 4);
        std::cout << "Error loading data! Please try again.";
        SetColor(7, 0);
        return;
    }
    std::ofstream write;
    std::string classcode;
    // Find the classcode
    int pos = directory.rfind('\\');
    fileName = directory.substr(pos + 1);
    int tmp = fileName.find('.');
    classcode = fileName.substr(0, tmp);
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
        SetColor(7, 4);
        std::cout << "\n\n"; gotox(mid - 119 / 2);
        std::cout << "Cannot find the class you've entered! Return to menu to add this class to the semester or reenter the available class!\n";
        SetColor(7, 0);
        gotox(mid - 28/2); system("pause");
        return;
    }
    student* curStudent = curClass->headS;
    write.open("../Data/Class/" + classcode + ".csv", std::ios::app);  // will make a copy of this .csv to the Data folder
    std::string redundant;      // the first line of the csv file 
    std::getline(read, redundant);   
    int line = 2;
    bool state = true;
    bool dups = false;
    student* tail = nullptr;
    while (!read.eof())
    {
        // info of a student
        int no;
        std::string id, firstname, lastname, socialId;
        int gender;
        date dob;
        std::string getNO;
        std::getline(read, getNO, ',');
        if (read.eof())
            break;
        if (!checkValidNum(getNO))
            state = false;
        else
            no = stoi(getNO);
        std::getline(read, id, ',');

        while (curStudent != nullptr)       // check whether that student ID exists in the student list or not
        {
            if (curStudent->getStudentID() == id)
            {
                SetColor(7, 4);
                gotox(mid - 60 / 2);
                std::cout << "At line " << line << ", student ID " << id << " already exists in the list" << "\n";
                SetColor(7, 0);
                dups = true;
                break;
            }
            if (curStudent->pNext == nullptr)
                tail = curStudent;
            curStudent = curStudent->pNext;
        }

        std::getline(read, firstname, ',');
        if (!checkValidName(firstname))
            state = false;
        std::getline(read, lastname, ',');
        if (!checkValidName(lastname))
            state = false;
        std::string getGender;
        std::getline(read, getGender, ',');
        if (!checkValidNum(getGender))
            state = false;
        else
        {
            gender = stoi(getGender);
            if (gender < 0 || gender > 1)
                state = false;
        }
        std::string getDay, getMonth, getYear;
        std::getline(read, getDay, '/');
        std::getline(read, getMonth, '/');
        std::getline(read, getYear, ',');
        int day = stoi(getDay);
        int month = stoi(getMonth);
        int year = stoi(getYear);
        if (!checkValidDate(day, month, year))
            state = false;

        read.ignore();
        std::getline(read, socialId);
        if (socialId.length() != 12)
            state = false;

        // Save student information to a text file
        if (state == true && dups == false)         
        {
            if (!curStudent->checkExistFile(id))
                exportNewStudentProfile(classcode, id, firstname, lastname, no, gender, day, month, year, socialId);
            student* newStudent = new student(no, id, firstname, lastname, gender, day, month, year, socialId, nullptr);
            if (curClass->headS == nullptr)
            {
                curClass->headS = newStudent;
                curStudent = curClass->headS;
            }
            else
            {
                tail->pNext = newStudent;
                tail = tail->pNext;
            }
            // Save the info of this student to a "copy" file
            write << no << "," << id << "," << firstname << "," << lastname << "," << gender << "," << day << "/" << month << "/" << year << ",'" << socialId << "\n";
        }
        else if (state == false && dups == false) {
            SetColor(7, 4);
            gotox(mid - 60 / 2);
            std::cout << "At line: " << line << ": wrong data format. System will ignore this line of data!" << "\n";
            SetColor(7, 0);
        }
        ++line;                         
        curStudent = curClass->headS;       // reset conditions for the next turn
        state = true;   
        dups = false;
    }
    read.close();
    write.close();
    std::cout << "\n\n"; gotox(mid - 48 / 2);
    loadingPage();
    gotox(mid - 27 / 2); std::cout << "                            ";
    gotoxy(mid - 10 / 2, -2); std::cout << "         ";
    SetColor(7, 2);
    gotox(mid - 20 / 2);
    std::cout << "Added Succesfully";
    SetColor(7, 0);
    Sleep(1000);
    gotox(mid - 20 / 2); std::cout << "                       ";
    gotox(mid - 20 / 2);
    system("pause");
    system("cls");
}
bool student::checkExistFile(std::string id)
{
    std::ifstream read;
    read.open("../Data/StudentProfile/" + id + ".csv");
    if (!read)
    {
        return false;
    }
    else
    {
        read.close();
        return true;
    }
}
void Class::loadStudent()
{   
    Class* curClass = pHeadClass;
    while (curClass != nullptr)
    {
        std::string className = curClass->Name;
        std::ifstream read("../Data/Class/" + className + ".csv");
        if (!read)
            break;
        std::string redundant;
        std::getline(read, redundant);
        student* curStudent = curClass->headS;
        while (!read.eof())
        {
            int no;
            std::string id, firstname, lastname, socialId;
            bool gender;
            date dob;
            std::string getNO;
            std::getline(read, getNO, ',');
            std::getline(read, id, ',');
            if (read.eof())
                break;
            no = stoi(getNO);
            std::getline(read, firstname, ',');
            std::getline(read, lastname, ',');
            std::string getGender;
            std::getline(read, getGender, ',');
            gender = stoi(getGender);
            std::string getDay, getMonth, getYear;
            std::getline(read, getDay, '/');
            std::getline(read, getMonth, '/');
            std::getline(read, getYear, ',');
            int day = stoi(getDay);
            int month = stoi(getMonth);
            int year = stoi(getYear);
            read.ignore();
            std::getline(read, socialId);
            student* newStudent = new student(no, id, firstname, lastname, gender, day, month, year, socialId, nullptr);
            if (curClass->headS == nullptr)
            {
                curClass->headS = newStudent;
                curStudent = curClass->headS;
            }
            else
            {
                curStudent->pNext = newStudent;
                curStudent = curStudent->pNext;
            }
        } 
        curClass = curClass->pNext;
        read.close();
    }
}
void Class::exportNewStudentProfile(std::string classcode, std::string id, std::string firstname, std::string lastname, int no, bool gender, int day, int month, int year, std::string socialID)
{
    std::ofstream write;
    write.open("../Data/StudentProfile/" + id + ".csv");
    write << no << "," << id << "," << firstname << "," << lastname << "," << gender << "," << day << "/" << month << "/" << year << ",";
    write << socialID << "," << classcode << "\n";
    write.close();

}

void Class::sortStudents(std::string classcode)
{
    Class* curClass = pHeadClass;
    for (curClass; curClass != nullptr; curClass = curClass->pNext)
    {
        if (curClass->Name == classcode)
            break;
    }
    if (!curClass)
        return;
    student* curStudent = curClass->headS;
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

void Class::viewStudentList()
{
    //display
    showingList();

    std::cout << "\n"; gotox(mid - 58 / 2);
    std::cout << "Enter the class to see a list of students in that class: ";
    std::string classcode;
    std::getline(std::cin, classcode);

    sortStudents(classcode);
    Class* curClass = pHeadClass;
    for (curClass; curClass != nullptr; curClass = curClass->pNext)
    {
        if (curClass->Name == classcode)
            break;
    }
    if (!curClass)
    {
        std::cout << "\n\n"; gotox(mid - 17 / 2);
        SetColor(7, 4);
        std::cout << "Class Not Found!";
        SetColor(7, 0);
        Sleep(1000);
        return;
    }
    student* curStudent = curClass->headS;
    //Clear to show the list
    system("cls");

    //Showing list
    showingStudentList(curStudent);

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
        curClass->headS = nullptr;
        curClass = curClass->pNext;
    }
}

void Class::showStudents(student*& pHead, short range, short& Pcur) {
    const int tableWidth = 62;
    const int tableX = mid + 6 - tableWidth / 2;
    const int tableY = 5;

    gotoxy((2*tableX+45) / 2, 3);
    std::cout << "Student's List";

    // Print table header
    gotoxy(tableX, tableY);
    std::cout << "No.   Student ID   First Name    Last Name         Gender\n";

    int i = tableY + 2;
    int k = 0;
    while (pHead != nullptr && k < range) {
        // Print student information in table format
        gotoxy(tableX, i);
        std::cout << i - tableY - 1 << ".    " << pHead->getStudentID() << "      ";
        gotoxy(tableX + 19, i);
        std::cout << pHead->getFirstName();
        gotoxy(tableX + 33, i);
        std::cout << pHead->getLastName();
        gotoxy(tableX + 51, i);
        std::cout << (pHead->getGender() == 0 ? "Male" : "Female");

        pHead = pHead->pNext;
        i++;
        k++;
        Pcur++;
    }

    drawBox(tableX - 2, tableY - 1, tableWidth, Pcur + 6);
    gotoxy(tableX, tableY+1);
    drawLine(62, tableX - 2);

    gotoxy(tableX-3, tableY + 2 + Pcur);
    drawLine(tableWidth, tableX - 2);
    std::cout << "\n\n";
    gotox(tableX - 2);
}



void Class::showPStudents(student*& pHead, short range, short& Pcur) {
    //Check if the last page
    if (Pcur % range == 0) {
        for (int i = 0; i < Pcur - range * 2; i++) pHead = pHead->pNext;
        Pcur -= range * 2;
    }
    else {
        for (int i = 0; i < Pcur - (Pcur % range) - range; i++) pHead = pHead->pNext;
        Pcur += -(Pcur % range) - range;
    }
}

int Class::getAllStudents(student* pHead) {
    int i = 0;
    for (; pHead; pHead = pHead->pNext, i++);
    return --i;
}

void Class::showingStudentList(student* pHead) {
    std::string displayk = "N";
    std::string* content = nullptr;
    bool EnterConfirm = 0;
    int yp = 6;
    short TH = 3;
    short range = 10;
    short Pcur = 0;
    int APages = getAllStudents(pHead) / range + 1;
    student* pTail = pHead;
    student* cur = pHead;
    if (!pTail) return;
    for (; pTail->pNext; pTail = pTail->pNext);

    system("cls");
    while (true) {

        switch (TH) {
        //Next page
        case 3: {
            if (cur == nullptr) {
                SetColor(7, 12);
                if (Pcur % range == 0 && Pcur != 0) gotoxy(mid - 25 / 2, range + 12);
                else gotoxy(mid - 25 / 2, Pcur % range + 12);
                std::cout << "You are at the last page";
                SetColor(7, 0);

                Sleep(1000);

                //Reset the command
                gotox(mid - 47 / 2);
                std::cout << "                                                          \r";

            }
            else {
                system("cls");
                drawBox(15, 2, 30, 23);
                Tutorial(content);
                showStudents(cur, range, Pcur);
                Description(range, APages, (Pcur - 1) / range + 1, Pcur, 52, 62);
            }
            yp = 6;
            break;
        }
        //Previous Page
        case 2: {
            if (Pcur <= range) {
                SetColor(7, 12);
                if (Pcur % range == 0 && Pcur != 0) gotoxy(mid - 25 / 2, range + 12);
                else gotoxy(mid - 25 / 2, Pcur % range + 12);
                std::cout << "You are at the first page";
                SetColor(7, 0);

                Sleep(2000);

                //Reset the command
                gotox(mid - 47 / 2);
                std::cout << "                                                          \r";

            }
            else {
                system("cls");
                drawBox(15, 2, 30, 23);
                Tutorial(content);
                showPStudents(cur, range, Pcur);
                showStudents(cur, range, Pcur);
                Description(range, APages, (Pcur - 1) / range + 1, Pcur, 52, 62);
            }
            yp = 6 + 4;
            break;
        }
        //Enter to confirm
        case 0: {
            EnterConfirm = 1;
            break;
        }
              //Change list
        case 1: {

            if (Pcur % range == 0 && Pcur != 0) gotoxy(mid - 50 / 2, range + 12);
            else gotoxy(mid - 50 / 2, Pcur % range + 12);
            std::cout << "Please enter the number you want to change list: ";
            getline(std::cin, displayk);

            if (displayk[0] <= '9' && displayk[0] >= '0') {
                int sample = stoi(displayk);
                if (sample > 25 || sample < 10) {
                    SetColor(7, 12);
                    std::cout << "\n\n"; gotox(mid - 42 / 2);
                    std::cout << "The range is too big or too small (10~25)!";
                    SetColor(7, 0);

                    Sleep(2000);

                    //Reset the command
                    gotox(mid - 47 / 2);
                    std::cout << "                                                          \r";
                    gotoxy(mid - 50 / 2, -3); std::cout << "                                                    ";
                }
                else {
                    //Reset everything
                    range = sample;
                    Pcur = 0;
                    cur = pHead;
                    APages = getAllClass() / range + 1;

                    //Draw again
                    system("cls");
                    drawBox(15, 2, 30, 23);
                    Tutorial(content);
                    showStudents(cur, range, Pcur);
                    Description(range, APages, (Pcur - 1) / range + 1, Pcur, 52, 62);
                }
            }
            yp = 6 + 8;
            break;
        }
        }
        if (EnterConfirm == 1) {
            if (Pcur % range == 0 && Pcur != 0) gotoy(range + 8);
            else gotoy(Pcur % range + 8);
            break;
        }
        TH = movingBarTutorial(16, 6, yp, 44, 18, 4, content);
    }
}

void Class::showScoreBoardOfClass()
{
    while (true)
    {
        std::string* content = new std::string[3];
        content[0] = "1. View GPA of students";
        content[1] = "2. View detail score of students";
        content[2] = "0. Go back";

        system("cls");
        drawHeader();
        drawBox(mid - 53 / 2, 8, 53, 5);

        gotoxy(mid - 61 / 2, 7); std::cout << "View the GPA of class or total of class in semester.";
        gotoxy(mid - 49 / 2, 9); std::cout << "1. View GPA of students";
        gotoxy(mid - 49 / 2, 10); std::cout << "2. View detail score of students";
        gotoxy(mid - 49 / 2, 11); std::cout << "0. Go back";
        int choice = 0;
        choice = movingBar(mid - 51 / 2, 9, 9 + choice, mid + 53 / 2, 11, 1, content);
        student * tmp = headS;
        switch (choice)
        {
        case 2:
            showingGPAList(tmp);
            break;
        case 1:
            showingDetailMarkList(tmp);
            break;
        case 0:
            return;
        }
    }
}

void Class::showGPAOfClass(student*& pHead, short range, short& Pcur)
{
    const int tableWidth = 62;
    const int tableX = mid + 6 - tableWidth / 2;
    const int tableY = 5;
    gotoxy((2 * tableX + 45) / 2, 3);
    std::cout << "Student's List";
    // Print table header
    gotoxy(tableX, tableY);
    std::cout << "No.   Student ID   Name                  SemGPA    TotalGPA\n\n";
    
    int i = tableY + 2;
    int k = 0;

    int tmp = 1;
    for (; pHead && k < range; pHead = pHead->pNext)
    {
        std::string dir = "../Data/SchoolYear/" + curSchoolYear->getYear() + "/" + "Sem" + std::to_string(curSemester->getSem()) + "/Class/" + curClass->getName() + "/" + pHead->getStudentID() + ".csv";
        std::ifstream fin(dir);
        std::string temp;
        double gpa{}, overall{};
        int credit{}, total{};
        if (fin.is_open())
        {
            std::string a;
            getline(fin, a);
            while (getline(fin, temp))                                  // GPA in semester
            {
                int pos1 = temp.find(',');
                int pos2 = temp.find(',', pos1 + 1);
                int pos3 = temp.find(',', pos2 + 1);
                int pos4 = temp.find(',', pos3 + 1);
                int pos5 = temp.find(',', pos4 + 1);
                std::string ToTal = temp.substr(0, pos1);
                std::string Credit = temp.substr(pos5+1, temp.length()-pos5-1);
                credit += stoi(Credit);
                gpa += stod(ToTal) * stoi(Credit);
            }
        }
        fin.close();
        
        std::string block = curSchoolYear->getYear().substr(2, 2);
        std::string yea = pHead->getStudentID().substr(0, 2);
        int firstY = stoi(block), id = stoi(yea);
        while(firstY >= id)
        {
            for (int i = 1; i <= 3; ++i)
            {
                int sem = i;

                std::string y = "20" + std::to_string(firstY) + "-" + "20" + std::to_string(firstY + 1);
                std::string path = "../Data/SchoolYear/" + y + "/" + "Sem" + std::to_string(sem)
                    + "/Class/" + curClass->getName() + "/" + pHead->getStudentID() + ".csv";
                fin.open(path);
                std::string temp;
                if (fin.is_open())
                {
                    std::string a;
                    getline(fin, a);
                    while (getline(fin, temp))                                  // Overall GPA
                    {
                        int pos1 = temp.find(',');
                        int pos2 = temp.find(',', pos1 + 1);
                        int pos3 = temp.find(',', pos2 + 1);
                        int pos4 = temp.find(',', pos3 + 1);
                        int pos5 = temp.find(',', pos4 + 1);
                        std::string ToTal = temp.substr(0, pos1);
                        std::string Credit = temp.substr(pos5+1, temp.length() - pos5 - 1);
                        total += stoi(Credit);
                        overall += stod(ToTal) * stoi(Credit);
                    }
                }
                fin.close();
            }
            firstY--;
        }
        gotox(tableX); std::cout << tmp++ << "     " << pHead->getStudentID() << "     " << pHead->getLastName() << " " << pHead->getFirstName();
        gotox(tableX + 42); 
        std::cout.setf(std::ios::fixed, std::ios::floatfield); std::cout.precision(2); 
        std::cout << gpa / credit;
        gotox(tableX + 53); std::cout << overall / total << std::endl;

        Pcur++;
        i++;
        k++;
    }

    drawBox(tableX - 2, tableY - 1, tableWidth, Pcur + 6);
    gotoxy(tableX, tableY + 1);
    drawLine(62, tableX - 2);
    gotoxy(tableX - 3, tableY + 2 + Pcur);
    drawLine(tableWidth, tableX - 2);
    std::cout << "\n\n";
    gotox(tableX - 2);
}

void viewClass()
{
    for (Class* cur = pHeadClass; cur; cur = cur->pNext)
        std::cout << cur->getName() << std::endl;
    std::cout << "Input your choice:";
    std::string name;
    getline(std::cin, name);
    for (Class* cur = pHeadClass; cur; cur = cur->pNext)
    {
        if (name == cur->getName())
        {
            curClass = cur;
            break;
        }
    }
}

void Class::showDetailMark(student*& pHead, short range, short& Pcur)
{
    const int tableWidth = 72;
    const int tableX = mid + 6 - tableWidth / 2;
    const int tableY = 5;
    gotoxy((2 * tableX + 55) / 2, 3);
    std::cout << "Student's List";
    // Print table header
    gotoxy(tableX, tableY);
    std::cout << "No.  Student ID  Name                   Course's ID        TotalScore\n\n";
    int i = tableY + 2;
    int k = 0;
    std::string id;


    int tmp = 1;

    while (k < range && pHead)
    {
        id = pHead->getStudentID();
        std::string dir = "../Data/SchoolYear/" + curSchoolYear->getYear() + "/" + "Sem" + std::to_string(curSemester->getSem()) + "/Class/" + curClass->getName() + "/" + id + ".csv";
        std::ifstream fin(dir);
        std::string temp;
        std::string id;

        if (fin.is_open())
        {
            std::string a;
            getline(fin, a);

            while (getline(fin, temp))                                  // GPA in semester
            {
                int pos1 = temp.find(',');
                int pos2 = temp.find(',', pos1 + 1);
                int pos3 = temp.find(',', pos2 + 1);
                int pos4 = temp.find(',', pos3 + 1);
                int pos5 = temp.find(',', pos4 + 1);
                std::string ToTal = temp.substr(0, pos1);
                std::string CourseId = temp.substr(pos4 + 1, pos5 - pos4 - 1);
                gotox(tableX); std::cout << tmp++;

                gotox(tableX + 5); std::cout << pHead->getStudentID();
                gotox(tableX + 17); std::cout << pHead->getLastName() << " " << pHead->getFirstName();
                gotox(tableX + 40); std::cout << CourseId;

                std::cout.setf(std::ios::fixed, std::ios::floatfield); std::cout.precision(2);
                gotox(tableX + 59); std::cout << ToTal << std::endl;
                Pcur++;
                k++;
                if (k+1 >= range) break;
            }
            fin.close();
        }
        if (k+1 >= range) break;
        pHead = pHead->pNext;
        if (!pHead) break;
    }

    drawBox(tableX - 2, tableY - 1, tableWidth, Pcur + 6);
    gotoxy(tableX, tableY + 1);
    drawLine(72, tableX - 2);
    gotoxy(tableX - 3, tableY + 2 + Pcur);
    drawLine(tableWidth, tableX - 2);
    std::cout << "\n\n";
    gotox(tableX - 2);

}

bool Class::getClass() {
    while (true) {
        system("cls");

        //Display pages
        if (pHeadClass != nullptr) showingList();
        else {
            drawHeader();
            std::cout << "\n"; gotox(mid - 29 / 2);
            SetColor(7, 4); std::cout << "There is no class currently!"; SetColor(7, 0);
        }

        //Enter the class code
        std::cout << "\n"; gotox(mid - 62 / 2);
        std::cout << "Please make sure to input valid class";

        std::cout << "\n"; gotox(mid - 62 / 2);
        std::cout << "Please enter the name of the class you want to choose";

        std::cout << "\n"; gotox(mid - 62 / 2);
        std::cout << "Press enter to stop: ";
        std::string Name;  getline(std::cin, Name);

        //if enter then return
        if (Name == "") return 0;

        //Check the class
        if (checkExistClass(Name) != 0) {
            std::cout << "\n"; gotox(mid - 29 / 2);
            SetColor(7, 12);
            std::cout << "This class is not exist.";
            SetColor(7, 0);

            Sleep(2000);
            continue;
        }

        //Check the class if correct to add
        else if (pHeadClass->CheckClasses(Name) == 0) {
            std::cout << "\n"; gotox(mid - 35 / 2);
            SetColor(7, 12);
            std::cout << "Please enter the class correctly.\n";
            SetColor(7, 0);

            Sleep(2000);
            continue;
        }
        for (Class* cur = pHeadClass; cur; cur = cur->pNext)
        {
            if (Name == cur->getName())
            {
                curClass = cur;
                break;
            }
        }
        return 1;
    }
}

void Class::showingGPAList(student* pHead) {
    std::string displayk = "N";
    std::string* content = nullptr;
    bool EnterConfirm = 0;
    int yp = 6;
    short TH = 3;
    short range = 10;
    short Pcur = 0;
    int APages = getAllStudents(pHead) / range + 1;
    student* pTail = pHead;
    student* cur = pHead;
    if (!pTail) return;
    for (; pTail->pNext; pTail = pTail->pNext);

    system("cls");
    while (true) {

        switch (TH) {
            //Next page
        case 3: {
            if (cur == nullptr) {
                SetColor(7, 12);
                if (Pcur % range == 0 && Pcur != 0) gotoxy(mid - 25 / 2, range + 12);
                else gotoxy(mid - 25 / 2, Pcur % range + 12);
                std::cout << "You are at the last page";
                SetColor(7, 0);

                Sleep(1000);

                //Reset the command
                gotox(mid - 47 / 2);
                std::cout << "                                                          \r";

            }
            else {
                system("cls");
                drawBox(15, 2, 30, 23);
                Tutorial(content);
                showGPAOfClass(cur, range, Pcur);
                Description(range, APages, (Pcur - 1) / range + 1, Pcur, 52, 62);
            }
            yp = 6;
            break;
        }
              //Previous Page
        case 2: {
            if (Pcur <= range) {
                SetColor(7, 12);
                if (Pcur % range == 0 && Pcur != 0) gotoxy(mid - 25 / 2, range + 12);
                else gotoxy(mid - 25 / 2, Pcur % range + 12);
                std::cout << "You are at the first page";
                SetColor(7, 0);

                Sleep(2000);

                //Reset the command
                gotox(mid - 47 / 2);
                std::cout << "                                                          \r";

            }
            else {
                system("cls");
                drawBox(15, 2, 30, 23);
                Tutorial(content);
                showPStudents(cur, range, Pcur);
                showGPAOfClass(cur, range, Pcur);
                Description(range, APages, (Pcur - 1) / range + 1, Pcur, 52, 62);
            }
            yp = 6 + 4;
            break;
        }
              //Enter to confirm
        case 0: {
            EnterConfirm = 1;
            break;
        }
              //Change list
        case 1: {

            if (Pcur % range == 0 && Pcur != 0) gotoxy(mid - 50 / 2, range + 12);
            else gotoxy(mid - 50 / 2, Pcur % range + 12);
            std::cout << "Please enter the number you want to change list: ";
            getline(std::cin, displayk);

            if (displayk[0] <= '9' && displayk[0] >= '0') {
                int sample = stoi(displayk);
                if (sample > 25 || sample < 10) {
                    SetColor(7, 12);
                    std::cout << "\n\n"; gotox(mid - 42 / 2);
                    std::cout << "The range is too big or too small (10~25)!";
                    SetColor(7, 0);

                    Sleep(2000);

                    //Reset the command
                    gotox(mid - 47 / 2);
                    std::cout << "                                                          \r";
                    gotoxy(mid - 50 / 2, -3); std::cout << "                                                    ";
                }
                else {
                    //Reset everything
                    range = sample;
                    Pcur = 0;
                    cur = pHead;
                    APages = getAllClass() / range + 1;

                    //Draw again
                    system("cls");
                    drawBox(15, 2, 30, 23);
                    Tutorial(content);
                    showGPAOfClass(cur, range, Pcur);
                    Description(range, APages, (Pcur - 1) / range + 1, Pcur, 52, 62);
                }
            }
            yp = 6 + 8;
            break;
        }
        }
        if (EnterConfirm == 1) {
            if (Pcur % range == 0 && Pcur != 0) gotoy(range + 8);
            else gotoy(Pcur % range + 8);
            break;
        }
        TH = movingBarTutorial(16, 6, yp, 44, 18, 4, content);
    }
}

void Class::showingDetailMarkList(student* pHead) {
    std::string displayk = "N";
    std::string* content = nullptr;
    bool EnterConfirm = 0;
    int yp = 6;
    short TH = 3;
    short range = 20;
    short Pcur = 0;
    int APages = getAllDetailMarks(pHead) / range + 1;
    student* pTail = pHead;
    student* cur = pHead;
    student* pPre = pHead;
    if (!pTail) return;
    for (; pTail->pNext; pTail = pTail->pNext);

    system("cls");
    while (true) {

        switch (TH) {
            //Next page
        case 3: {
            if (cur == nullptr) {
                SetColor(7, 12);
                if (Pcur % range == 0 && Pcur != 0) gotoxy(mid - 25 / 2, range + 12);
                else gotoxy(mid - 25 / 2, Pcur % range + 12);
                std::cout << "You are at the last page";
                SetColor(7, 0);

                Sleep(2000);

                //Reset the command
                gotox(mid - 47 / 2);
                std::cout << "                                                          \r";

            }
            else {
                system("cls");
                drawBox(15, 2, 30, 23);
                Tutorial(content);
                showDetailMark(cur, range, Pcur);
                Description(range, APages, (Pcur - 1) / range + 1, Pcur, 47, 72);
            }
            yp = 6;
            break;
        }
              //Previous Page
        case 2: {
            if (Pcur <= range) {
                SetColor(7, 12);
                if (Pcur % range == 0 && Pcur != 0) gotoxy(mid - 25 / 2, range + 12);
                else gotoxy(mid - 25 / 2, Pcur % range + 12);
                std::cout << "You are at the first page";
                SetColor(7, 0);

                Sleep(2000);

                //Reset the command
                gotox(mid - 47 / 2);
                std::cout << "                                                          \r";

            }
            else {
                system("cls");
                drawBox(15, 2, 30, 23);
                Tutorial(content);
                showPStudents(cur, range, Pcur);
                showDetailMark(cur, range, Pcur);
                Description(range, APages, (Pcur - 1) / range + 1, Pcur, 47, 72);
            }
            yp = 6 + 4;
            break;
        }
              //Enter to confirm
        case 0: {
            EnterConfirm = 1;
            break;
        }
              //Change list
        case 1: {

            if (Pcur % range == 0 && Pcur != 0) gotoxy(mid - 50 / 2, range + 12);
            else gotoxy(mid - 50 / 2, Pcur % range + 12);
            std::cout << "Please enter the number you want to change list: ";
            getline(std::cin, displayk);

            if (displayk[0] <= '9' && displayk[0] >= '0') {
                int sample = stoi(displayk);
                if (sample > 25 || sample < 10) {
                    SetColor(7, 12);
                    std::cout << "\n\n"; gotox(mid - 42 / 2);
                    std::cout << "The range is too big or too small (10~25)!";
                    SetColor(7, 0);

                    Sleep(2000);

                    //Reset the command
                    gotox(mid - 47 / 2);
                    std::cout << "                                                          \r";
                    gotoxy(mid - 50 / 2, -3); std::cout << "                                                    ";
                }
                else {
                    //Reset everything
                    range = sample;
                    Pcur = 0;
                    cur = pHead;
                    APages = getAllDetailMarks(cur) / range + 1;

                    //Draw again
                    system("cls");
                    drawBox(15, 2, 30, 23);
                    Tutorial(content);
                    showDetailMark(cur, range, Pcur);
                    Description(range, APages, (Pcur - 1) / range + 1, Pcur, 47, 72);
                }
            }
            yp = 6 + 8;
            break;
        }
        }
        if (EnterConfirm == 1) {
            if (Pcur % range == 0 && Pcur != 0) gotoy(range + 8);
            else gotoy(Pcur % range + 8);
            break;
        }
        TH = movingBarTutorial(16, 6, yp, 44, 18, 4, content);
    }
}

int Class::getAllDetailMarks(student* pHead) {
    int i = 0;
    for (; pHead; pHead = pHead->pNext) {
        std::string id = pHead->getStudentID();
        std::string dir = "../Data/SchoolYear/" + curSchoolYear->getYear() + "/" + "Sem" + std::to_string(curSemester->getSem()) + "/Class/" + curClass->getName() + "/" + id + ".csv";
        std::ifstream fin(dir);
        std::string temp;

        if (fin.is_open())
        {
            std::string a;
            getline(fin, a);

            while (getline(fin, temp)) {
                i++;
            }
        }
    }
    return i;
}
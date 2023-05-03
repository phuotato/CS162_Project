#include "Course.h"
#include <fstream>
#include <direct.h>
#include <string>
#include "Graphic.h"
//Constructor
course::course(std::string id, std::string name, std::string className, std::string lecturer, int credit, int maxStudent, int weekDay, int session)
    :id(id), name(name), className(className), lecturer(lecturer), credit(credit), maxStudent(maxStudent), weekDay(weekDay), session(session) {};
void course::ExportClass()
{
    std::ofstream fout;
    fout.open("../Scoreboard/" + id + "_scoreboard.csv");

    //File header
    fout << "No,Student ID,First name,Last name" << "\n";

    int i = 1;
    studentScore* current = hScore;
    while (current) 
    {
        fout << i++ << ",";
        fout << current->studentID << ",";
        fout << current->firstName << ",";
        fout << current->lastName << ",";

        current = current->pNext;
    }

    fout.close();

    std::cout << "Finished exporting to " << id << "_scoreboard.csv\n";
}

void course::ImportScoreboard()
{
    std::ifstream fin("../Scoreboard/" + id + "_scoreboard.csv");
    if (!fin)
    {
        std::cout << "Error loading file! Please try again.";
        return;
    }
    std::string header;
    std::getline(fin, header); // ignore the header row of csv

    while (!fin.eof())
    {
        std::string studentID, firstName, lastName, totalMarkStr, finalMarkStr, midtermMarkStr, otherMarkStr;
        double totalMark, finalMark, midtermMark, otherMark;

        std::getline(fin, studentID, ',');
        if (studentID.empty() || fin.eof()) // check if we have reached the end of the file
            break;

        std::getline(fin, firstName, ',');
        std::getline(fin, lastName, ',');
        std::getline(fin, totalMarkStr, ',');
        std::getline(fin, finalMarkStr, ',');
        std::getline(fin, midtermMarkStr, ',');
        std::getline(fin, otherMarkStr, '\n');

        try {
            totalMark = std::stod(totalMarkStr);
            finalMark = std::stod(finalMarkStr);
            midtermMark = std::stod(midtermMarkStr);
            otherMark = std::stod(otherMarkStr);
        }
        catch (const std::exception& e) {
            std::cout << "Error: Invalid data format in file. Please check again.\n";
            return;
        }

        studentScore* newScore = new studentScore{ studentID, firstName, lastName, totalMark, finalMark, midtermMark, otherMark, nullptr };
        if (!hScore)
        {
            hScore = newScore;
        }
        else
        {
            studentScore* pCur = hScore;
            while (pCur->pNext)
                pCur = pCur->pNext;
            pCur->pNext = newScore;
        }
    }

    fin.close();
    std::cout << "Import successful!\n";
}

void course::updateCourse()
{
    while(true)
    {
        system("cls");
        std::cout << "1.Id:" << id << std::endl;
        std::cout << "2.Name:" << name << std::endl;
        std::cout << "3.Class name:" << className << std::endl;
        std::cout << "4.Lecturer:" << lecturer << std::endl;
        std::cout << "5.Credit:" << credit << std::endl;
        std::cout << "6.Max student:" << maxStudent << std::endl;
        std::cout << "7.Day performed per week:" << weekDay << std::endl;
        std::cout << "8.Session:";
        switch (session)
        {
        case 1:
            std::cout << "07:30\n";
            break;
        case 2:
            std::cout << "09:30\n";
            break;
        case 3:
            std::cout << "13:30\n";
        case 4:
            std::cout << "15:30\n";
        }
        std::cout << "Chose the number you want to edit (Press enter to back):";
        std::string choice; getline(std::cin, choice);
        if (choice == "")
            break;
        int ch = stoi(choice);
        std::string New;
        int NEw;
        switch (ch)
        {
        case 1:
            std::cout << "Input the New one:";
            getline(std::cin, New);
            id = New;
            break;
        case 2:
            std::cout << "Input the New one:";
            getline(std::cin, New);
            name = New;
            break;
        case 3:
            std::cout << "Input the New one:";
            getline(std::cin, New);
            className = New;
            break;
        case 4:
            std::cout << "Input the New one:";
            getline(std::cin, New);
            lecturer = New;
            break;
        case 5:
            std::cout << "Input the New one:";
            std::cin>>NEw;
            credit = NEw;
            break;
        case 6:
            std::cout << "Input the New one:";
            std::cin >> NEw;
            maxStudent = NEw;
            break;
        case 7:
            std::cout << "Input the New one:";
            std::cin >> NEw;
            weekDay = NEw;
            break;
        case 8:
            std::cout << "Input the New one:";
            std::cin >> NEw;
            session = NEw;
            break;
        }
    }
}

void course::addStudentMenu()
{
    int choice;
    do
    {
        system("cls");
        drawHeader();

        std::cout << "\n\t\t+--------------------------------------------------+";
        std::cout << "\n\t\t| 1. Add student manually                          |";
        std::cout << "\n\t\t| 2. Import csv file                               |"; //chua lam
        std::cout << "\n\t\t| 0. Back                                          |";
        std::cout << "\n\t\t+--------------------------------------------------+";
        std::cout << "\n\t\t Enter your choice: ";
        std::cin >> choice;
        if (choice)
            addStudent(choice);
    } while (choice);
}

void course::addStudent(int choice)
{
    char ch = 'Y';
    do
    {
        if (choice == 1)
        {
            system("cls");
            bool gender;
            std::string id, firstname, lastname, dob, socialId;
            system("cls");
            std::cout << "Id:";
            std::cin.ignore();
            getline(std::cin, id);
            std::cout << "Frist name:";
            getline(std::cin, firstname);
            std::cout << "Last name:";
            getline(std::cin, lastname);
            std::cout << "Gender:";
            std::cin >> gender;
            std::cout << "Date of birth(dd/mm/yyyy):";
            std::cin.ignore();
            getline(std::cin, dob);
            std::cout << "Social id:";
            getline(std::cin, socialId);
            if (pHeadStudent)
            {
                if (compareString(lastname, pHeadStudent->getLastName(), firstname, pHeadStudent->getFirstName()) <= 0)
                {
                    student* tmp = new student(pHeadStudent->getNo(), id, firstname, lastname, gender, dob, socialId);
                    tmp->pNext = pHeadStudent;
                    pHeadStudent = tmp;
                    for (student* cur = pHeadStudent->pNext; cur; cur = cur->pNext)
                        cur->increaseNo();

                }
                else if (compareString(lastname, pTailStudent->getLastName(), firstname, pTailStudent->getFirstName()) >= 0)
                {
                    pTailStudent->pNext = new student(pTailStudent->getNo() + 1, id, firstname, lastname, gender ,dob, socialId);
                    pTailStudent = pTailStudent->pNext;
                }
                else
                {
                    for (student* cur = pHeadStudent; cur->pNext; cur = cur->pNext)
                    {
                        if (  (compareString(lastname, cur->getLastName(), firstname, cur -> getFirstName()) >= 0) && (compareString(lastname, cur->pNext->getLastName(), firstname, cur->pNext->getFirstName()) <= 0))
                        {
                            student* tmp= new student(cur->getNo() + 1, id, firstname, lastname, gender, dob, socialId);
                            tmp->pNext = cur->pNext;
                            cur->pNext = tmp;
                            for (student* temp = cur->pNext->pNext; temp; temp = temp->pNext)
                                temp->increaseNo();
                            break;
                        }
                    }
                }
            }
            else
            {
                pHeadStudent= new student(1, id, firstname, lastname, gender, dob, socialId);
                pTailStudent = pHeadStudent;
            }
            std::cout << "Add student successfully. Do you want to add more (Y/y to continue N/n to stop):";
            std::cin >> ch;
        }
        else
        {
            std::cout << "Input the directory:";
            std::string dir;
            std::cin.ignore();
            getline(std::cin, dir);
            std::ifstream fin;
            fin.open(dir);
            {
                std::string redundant;
                getline(fin, redundant);
                if (!pHeadStudent)
                {
                    while(!fin.eof())
                    {
                        std::string no,id, gender, firstname, lastname, dob, socialId;
                        getline(fin, no, ',');
                        getline(fin, id, ',');
                        getline(fin, firstname, ',');
                        getline(fin, lastname, ',');
                        getline(fin, gender, ',');
                        getline(fin, dob, ',');
                        fin.get();
                        getline(fin, socialId);
                        if (pHeadStudent)
                        {
                            pHeadStudent = new student(stoi(id), id, firstname, lastname, stoi(gender), dob, socialId);
                            pTailStudent = pHeadStudent;
                        }
                        else
                        {
                            pTailStudent->pNext = new student(stoi(id), id, firstname, lastname, stoi(gender), dob, socialId);
                            pTailStudent = pTailStudent->pNext;
                        }
                    }
                }
                else
                {
                    student* headStudent = nullptr, *tailStudent = nullptr;
                    int count = 1;
                    while (!fin.eof())
                    {
                        std::string no, id, gender, firstname, lastname, dob, socialId;
                        getline(fin, no, ',');
                        getline(fin, id, ',');
                        getline(fin, firstname, ',');
                        getline(fin, lastname, ',');
                        getline(fin, gender, ',');
                        getline(fin, dob, ',');
                        getline(fin, socialId);
                        if (!headStudent)
                        {
                            headStudent = new student(stoi(no), id, firstname, lastname, stoi(gender), dob, socialId);
                            tailStudent = headStudent;
                        }
                        else
                        {
                            tailStudent->pNext = new student(stoi(no), id, firstname, lastname, stoi(gender), dob, socialId);
                            tailStudent = tailStudent->pNext;
                        }
                        if (pHeadStudent && id == pHeadStudent->getStudentID())
                        {
                            std::cout << "Error! Line " << count << " is already add in this course\n";
                            student* tmp = pHeadStudent;
                            pHeadStudent = pHeadStudent->pNext;
                            delete tmp;
                        }
                        ++count;
                    }
                    pHeadStudent = headStudent;
                    pTailStudent = tailStudent;
                }
            }
            fin.close();
            std::cout << "Add student successfully. Press any key to back:";
            _getch();
            break;
        }
    } while (ch != 'N' && ch!='n');
}

int compareString(std::string a, std::string b, std::string c, std::string d)
{
    std::string firstA, secondA, firstB, secondB;
    for (int i = a.length() - 1; ; --i)
    {
        if (a[i] == ' ')
        {
            firstA = a.substr(0, i);
            secondA = a.substr(i + 1, a.length() - i + 1);
            break;
        }
    }
    for (int i = b.length() - 1; ; --i)
    {
        if (b[i] == ' ')
        {
            firstB = b.substr(0, i);
            secondB = b.substr(i + 1, b.length() - i + 1);
            break;
        }
    }
    if (secondA < secondB)
        return -1;
    if (secondA > secondB)
        return 1;
    if (firstA < firstB)
        return -1;
    if (firstA > firstB)
        return 1;
    if (c < d)
        return -1;
    if (c > d)
        return 1;
    return 0;
}

void course::showStudent()
{
    system("cls");
    for (student* cur = pHeadStudent; cur; cur = cur->pNext)
    {
        std::cout << "No:" << cur->getNo() << std::endl;
        std::cout << "Id:" << cur->getStudentID() << std::endl;
        std::cout << "First name:" << cur->getFirstName() << std::endl;
        std::cout << "Last name:" << cur->getLastName() << std::endl;
        std::cout << "Gender:";
        switch (cur->getGender())
        {
        case 0:
            std::cout << "Male\n";
            break;
        case 1:
            std::cout << "Female\n";
            break;
        }
        std::cout << "Date of birth:" << cur->getDate() << std::endl;
        std::cout << "Social id:" << cur->getSocialId() << std::endl << std::endl;
    }
    std::cout << "Press any key to coninue";
    _getch();
}

void course::showInfo()
{
    system("cls");
    std::cout << "1.Id:" << id << std::endl;
    std::cout << "2.Name:" << name << std::endl;
    std::cout << "3.Class name:" << className << std::endl;
    std::cout << "4.Lecturer:" << lecturer << std::endl;
    std::cout << "5.Credit:" << credit << std::endl;
    std::cout << "6.Max student:" << maxStudent << std::endl;
    std::cout << "7.Day performed per week:" << weekDay << std::endl;
    std::cout << "8.Session:";
    switch (session)
    {
    case 1:
        std::cout << "07:30\n";
        break;
    case 2:
        std::cout << "09:30\n";
        break;
    case 3:
        std::cout << "13:30\n";
    case 4:
        std::cout << "15:30\n";
    }
    std::cout << "Press any key to back:";
    _getch();
}
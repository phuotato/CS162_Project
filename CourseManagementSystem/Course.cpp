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

void course::addStudent()
{
    int choice;
    do
    {
        system("cls");
        drawHeader();

        std::cout << "\n\t\t+--------------------------------------------------+";
        std::cout << "\n\t\t| 1. Add student mannually                         |";
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
    if (choice == 1)
    {
        char ch = 'Y';
        do
        {
            std::string no, id, firstName, lastName, gender, socialId, dob;
            std::cin.ignore();
            std::cout << "\n\t\tNo:"; getline(std::cin, no);
            std::cout << "\n\t\tStudent id:"; getline(std::cin, id);
            std::cout << "\n\t\tLast name:"; getline(std::cin, lastName);
            std::cout << "\n\t\tFirst name:"; getline(std::cin, firstName);
            std::cout << "\n\t\tGender:"; getline(std::cin, gender);
            std::cout << "\n\t\tDate of birth:"; getline(std::cin, dob);
            std::cout << "\n\t\tSocial id:"; getline(std::cin, socialId);
            if (pHeadStudent)
            {
                pTailStudent->pNext = new student(stoi(no), id, firstName, lastName, stoi(gender), dob, socialId);
                pTailStudent = pTailStudent->pNext;
            }
            else
            {
                pHeadStudent = new student(stoi(no), id, firstName, lastName, stoi(gender), dob, socialId);
                pTailStudent = pHeadStudent;
            }
            std::cout << "Add successfully. Do you want to add more (Press Y/y to continue, N/n to stop):";
            std::cin >> ch;
        } while (ch != 'N' && ch != 'n');
    }
    if (choice == 2)
    {
        std::cout << "Input your directory:";
        std::string dir;
        getline(std::cin, dir);
        std::ifstream fin(dir);
        if (!fin.is_open())
            std::cout << "Khong the mo";
        else
        {
            std::string redundant;
            getline(fin, redundant);
            while (!fin.eof())
            {
                std::string no, id, firstName, lastName, gender, socialId, dob;
                getline(fin, no, ',');
                getline(fin, id, ',');
                getline(fin, lastName, ',');
                getline(fin, firstName, ',');
                getline(fin, gender, ',');
                getline(fin, dob, ',');
                getline(fin, socialId);
                if (pHeadStudent)
                {
                    pTailStudent->pNext = new student(stoi(no), id, firstName, lastName, stoi(gender), dob, socialId);
                    pTailStudent = pTailStudent->pNext;
                }
                else
                {
                    pHeadStudent= new student(stoi(no), id, firstName, lastName, stoi(gender), dob, socialId);
                    pTailStudent = pHeadStudent;
                }
            }
        }
    }
}

void course::loadClass()
{

}

void course::showStudent()
{
    if (!pHeadStudent)
    {
        std::cout << "This class haven't been add any student before";
        std::cout << "Press any key to continue:";
        _getch();
        return;
    }
    for (student* cur = pHeadStudent; cur; cur = cur->pNext)
    {
        std::cout << "No:" << cur->getNo() << std::endl;
        std::cout << "Student id:" << cur->getStudentID()<<std::endl;
        std::cout << "Last name:" << cur->getLastName()<<std::endl;
        std::cout << "FIrst name:" << cur->getFirstName()<<std::endl;
        std::cout << "Gender:";
        switch (cur->getGender())
        {
        case 1:
            std::cout << "Female" << std::endl;
            break;
        case 0:
            std::cout << "Male" << std::endl;
            break;
        }
        std::cout << "Date of birth:" << cur->getDate() << std::endl;
        std::cout << "Social id:" << cur->getSocialId() << std::endl << std::endl;
    }
    std::cout << "Press any key to continue:";
    _getch();
}
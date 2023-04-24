#include "Course.h"
#include <fstream>
#include <direct.h>
#include <string>
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
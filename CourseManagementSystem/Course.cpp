#include "Course.h"
#include "schoolYear.h"
#include "Semester.h"
#include "Graphic.h"
#include <fstream>
#include <direct.h>
#include <string>

//global variable
extern schoolYear* curSchoolYear;
extern semester* curSemester;
extern int mid;

//Constructor
course::course(std::string id, std::string name, std::string className, std::string lecturer, int credit, int maxStudent, int weekDay, int session)
    :id(id), name(name), className(className), lecturer(lecturer), credit(credit), maxStudent(maxStudent), weekDay(weekDay), session(session) {};

void course::ExportClass()
{
    std::ofstream fout;
    std::cout << "The format of the course ID is: CourseName_ClassName. \n\n";
    std::cout << "Input the course ID: ";
    std::string courseID;
    std::getline(std::cin, courseID);

    fout.open("../InputFile/" + courseID + "_scoreboard.csv");

    //File header
    fout << "No,Student ID,First name,Last name" << "\n";

    int i = 1;
    course* curCourse = curSemester->pHeadCourse;
    for (curCourse; curCourse != nullptr; curCourse = curCourse->pNext)
    {
        if (curCourse->id == courseID)
            break;
    }
    if (!curCourse)
    {
        std::cout << "This semester doesn't have this course! Please try again!\n";
        system("pause");
        return;
    }
    studentScore* current = curCourse->hScore;
    while (current) 
    {
        fout << i++ << ",";
        fout << current->studentID << ",";
        fout << current->firstName << ",";
        fout << current->lastName << ",";
        fout << "\n";
        current = current->pNext;
    }

    fout.close();
    gotoxy(mid - 86 / 2, 5);
    std::cout << "Finished exporting to " << id << "_scoreboard.csv\n";
    system("pause");
    system("cls");
}

void course::ImportScoreboard()
{
    std::cout << "The format of the file should be: ../CourseID_scoreboard.csv" << "\n";
    std::cout << "For example: D:/Data/Score/PH212_22CTT2_scoreboard.csv \n\n";

    std::cout << "Import the link of the scoreboard of the course: ";
    std::string direct;
    std::getline(std::cin, direct);
    std::ifstream fin(direct);

    if (!fin)
    {
        std::cout << "Error loading file! Please try again.";
        return;
    }
    // get the ID of the course with the given directory
    int slashPosition = direct.rfind('\\');
    std::string csvFileName = direct.substr(slashPosition + 1);
    int pos = csvFileName.rfind('_');
    std::string courseID = csvFileName.substr(0, pos);
    
    
    if (_mkdir(("../Data/SchoolYear/" + curSchoolYear->year + "/Sem" + std::to_string(curSemester->sem) + "/" + courseID).c_str())); //create folder of that course if not exist
    std::ofstream fout("../Data/SchoolYear/" + curSchoolYear->year + "/Sem" + std::to_string(curSemester->sem) + "/" + courseID + "/score.csv");
    fout << "No,Student ID,First name,Last name,Total,Final,Midterm,Other" << "\n"; // first line of the CSV
    std::string header;
    std::getline(fin, header); // ignore the header row of csv

    // search for the course in the list
    course* curCourse = curSemester->pHeadCourse;
    for (curCourse; curCourse != nullptr; curCourse = curCourse->pNext)
    {
        if (curCourse->id == courseID)  // Found!
            break;
    }
    if (!curCourse) // Not found
    {
        std::cout << "This semester doesn't have this course!\n";
        system("pause");
        return;
    }
    int line = 2;   
    while (!fin.eof())
    {
        std::string getNo,studentID, firstName, lastName, totalMarkStr, finalMarkStr, midtermMarkStr, otherMarkStr;
        double totalMark, finalMark, midtermMark, otherMark;

        std::getline(fin, studentID, ',');
        if (studentID.empty() || fin.eof()) // check if we have reached the end of the file
            break;
        
        // get information from the file
        std::getline(fin, getNo, ',');
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
            std::cout << "Error in line " << line << ": Invalid data format in file. Please check again.\n";
            continue;
        }
        if (totalMark > 10 || totalMark < 0 || finalMark > 10 || finalMark < 0 || midtermMark > 10 || midtermMark < 0 || otherMark > 10 || otherMark < 0)
        {
            std::cout << "Error in line " << line << ": Invalid data format in file!" << "\n";
            continue;
        }
        studentScore* newScore = new studentScore{ studentID, firstName, lastName, totalMark, finalMark, midtermMark, otherMark, nullptr };
        if (!curCourse->hScore)
        {
            hScore = newScore;
        }
        else
        {
            studentScore* pCur = curCourse->hScore;
            while (pCur->pNext)
                pCur = pCur->pNext;
            pCur->pNext = newScore;
        }
        // Save the score to the score.csv
        fout << getNo << "," << studentID << "," << firstName << "," << lastName << "," << totalMark << "," << finalMark << "," << midtermMark << "," << otherMark << "\n";
        ++line;
    }
    fin.close(); 
    fout.close();
    saveIndividualScore(curCourse);      // save score after importing 
    std::cout << "Import successful!\n";
    system("pause");
    system("cls");
}

void course::updateStudentResult()
{
    std::cout << "Enter the course which the student's result need to be updated: ";
    std::string courseID;
    std::getline(std::cin, courseID);
    std::string studentID;
    std::cout << "Enter student ID: ";
    getline(std::cin, studentID, '\n');
    course* curCourse = curSemester->pHeadCourse;
    for (curCourse; curCourse != nullptr; curCourse = curCourse->pNext)
    {
        if (curCourse->id == courseID)
            break;
    }
    if (!curCourse)
    {
        std::cout << "This semester doesn't have this course! Please try again!\n";
        system("pause");
        return;
    }
    studentScore* pCur = curCourse->hScore;
    while (pCur && pCur->studentID != studentID)
        pCur = pCur->pNext;

    if (!pCur)
    {
        std::cout << "Student not found!\n";
        system("pause");
        return;
    }

    std::cout << "Enter the updated scores for " << pCur->firstName << " " << pCur->lastName << " (student ID: " << pCur->studentID << ")\n";
    std::cout << "Total Mark: ";
    std::cin >> pCur->totalMark;
    std::cout << "Final Mark: ";
    std::cin >> pCur->finalMark;
    std::cout << "Midterm Mark: ";
    std::cin >> pCur->midtermMark;
    std::cout << "Other Mark: ";
    std::cin >> pCur->otherMark;

    std::cout << "Scores updated successfully!\n";

    // update mssv.csv
    std::string direct = "../Data/SchoolYear/" + curSchoolYear->year + "/Sem" + std::to_string(curSemester->sem) + "/" + pCur->studentID + ".csv";
    std::ifstream read(direct);
    std::ofstream write(direct);
    std::string temp;
    while (std::getline(read, temp))
    {
        int posComma = temp.find(',');
        std::string ID = temp.substr(0, posComma);
        if (ID == courseID)
        {
            write << courseID << "," << pCur->totalMark << "," << pCur->finalMark << "," << pCur->midtermMark << "," << pCur->otherMark << "\n";
            break;
        }
    }
    read.close();
    write.close();

    // update score.csv
    std::ofstream write("../Data/SchoolYear/" + curSchoolYear->year + "/Sem" + std::to_string(curSemester->sem) + "/" + courseID + "/score.csv");
    std::ifstream read("../Data/SchoolYear/" + curSchoolYear->year + "/Sem" + std::to_string(curSemester->sem) + "/" + courseID + "/score.csv");
    while (std::getline(read, temp))
    {
        int pos1 = temp.find(',');
        int pos2 = temp.find(',', pos1 + 1);
        int pos3 = temp.find(',', pos2 + 1);
        int pos4 = temp.find(',', pos3 + 1);
        std::string tmpID = temp.substr(pos1 + 1, pos2 - pos1 - 1);
        if (tmpID == studentID)
        {
            // Rewrite the information in this line No->StudentID->FirstName->LastName->.....
            write << temp.substr(0, pos1) << "," << temp.substr(pos1 + 1, pos2 - pos1 - 1) << ","
                << temp.substr(pos2 + 1, pos3 - pos2 - 1) << "," << temp.substr(pos3 + 1, pos4 - pos3 - 1) << ","
                << pCur->totalMark << "," << pCur->finalMark << "," << pCur->midtermMark << "," << pCur->otherMark << "\n";
            break;
        }
    }
    read.close();
    write.close();
}


void course::ViewScoreboard() {
    system("cls");
    std::cout << "The format of a course ID is NameOfCourse_Classcode. For example: CS162_22CTT2" << "\n\n";
    std::cout << "Enter the course ID: ";
    std::string courseID;
    std::getline(std::cin, courseID);
    std::ifstream fin("../Data/SchoolYear/score.csv");
    // Get the number of students
    int numStudents = 0;
    studentScore* currScore = curSemester->pHeadCourse->hScore;
    while (currScore != nullptr) {
        numStudents++;
        currScore = currScore->pNext;
    }

    // Draw a box around the entire scoreboard
    drawBox(1, 1, 94, numStudents + 7);

    // Print the header row
    drawBox(2, 2, 90, 3);
    gotoxy(4, 3);
    std::cout << std::left << std::setw(10) << "No."
        << std::setw(12) << "ID"
        << std::setw(20) << "Name"
        << std::setw(12) << "Total"
        << std::setw(12) << "Final"
        << std::setw(12) << "Midterm"
        << std::setw(12) << "Other";

    // Iterate over the linked list and print each student's data
    int row = 5; // start at row 5
    int no = 1;
    currScore = curSemester->pHeadCourse->hScore;
    std::string firstline;
    std::getline(fin, firstline);
    while (currScore) {
        // Print the row number
        gotoxy(4, row);
        std::cout << std::left << std::setw(10) << no;

        // Print the student data
        std::cout << std::setw(12) << currScore->studentID
            << std::setw(20) << currScore->firstName+ " " + currScore->lastName
            << std::setw(12) << currScore->totalMark
            << std::setw(12) << currScore->finalMark
            << std::setw(12) << currScore->midtermMark
            << std::setw(12) << currScore->otherMark;
        row++;
        no++;
    }

    // Draw a box around the bottom of the scoreboard
    drawBox(2, row, 90, 3);
}
bool course::checkExistScoringFile(std::string direct)
{
    std::ifstream read(direct);
    if (!read)
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
void course::saveIndividualScore(course* curCourse) {
    // Iterate over the linked list of students
    studentScore* currScore = curCourse->hScore;
    while (currScore != nullptr) {
        std::string direct = "../Data/SchoolYear/" + curSchoolYear->year + "/Sem" + std::to_string(curSemester->sem) + "/" + currScore->studentID + ".csv";
        std::ofstream fout(direct, std::fstream::app);
        if (!checkExistScoringFile(direct))
            fout << "Course ID,Total Mark,Final Mark,Midterm Mark,Other Mark\n";
        fout << curCourse->id << "," << currScore->totalMark << ","
            << currScore->finalMark << ","
            << currScore->midtermMark << ","
            << currScore->otherMark << "\n";
        fout.close();
        currScore = currScore->pNext;
    }
    std::cout << "\n\t\tSaving successful!\n";
}

void course::updateCourse()
{
    std::ofstream fout;
    while(true)
    {
        system("cls");
        //header
        drawHeader();

        std::cout << "\n"; gotox(mid - 49 / 2);
        std::cout << "1.Id:" << id << std::endl;
        gotox(mid - 49 / 2); std::cout << "2.Name:" << name << std::endl;
        gotox(mid - 49 / 2); std::cout << "3.Class name:" << className << std::endl;
        gotox(mid - 49 / 2); std::cout << "4.Lecturer:" << lecturer << std::endl;
        gotox(mid - 49 / 2); std::cout << "5.Credit:" << credit << std::endl;
        gotox(mid - 49 / 2); std::cout << "6.Max student:" << maxStudent << std::endl;
        gotox(mid - 49 / 2); std::cout << "7.Day performed per week:" << weekDay << std::endl;
        gotox(mid - 49 / 2); std::cout << "8.Session:";
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
            break;
        case 4:
            std::cout << "15:30\n";
        }
        gotox(mid - 49 / 2); std::cout << "Choose the number you want to edit (Press enter to stop): ";
        std::string choice; getline(std::cin, choice);
        if (choice == "") break;

        while (choice <= "0" || choice >= "9" || choice.length() >= 2) {
            if (choice == "") break;

            std::cout << "\n"; gotox(mid - 24 / 2);
            SetColor(7, 4); std::cout << "Please input correctly!"; SetColor(7, 0);

            Sleep(1000);

            //Reset
            gotox(mid - 24 / 2); std::cout << "                       ";
            gotoxy(mid + 68 / 2, -2); std::cout << "                ";
            gotox(mid + 68 / 2);

            getline(std::cin, choice);
        }

        int ch = stoi(choice);
        std::string New;
        int NEw;
        gotox(mid - 49 / 2); std::cout << "Input the New one:";

        switch (ch)
        {
        case 1:
            getline(std::cin, New);
            id = New;
            break;
        case 2:
            getline(std::cin, New);
            name = New;
            break;
        case 3:
            getline(std::cin, New);
            className = New;
            break;
        case 4:
            getline(std::cin, New);
            lecturer = New;
            break;
        case 5:
            std::cin>>NEw;
            credit = NEw;
            break;
        case 6:
            std::cin >> NEw;
            maxStudent = NEw;
            break;
        case 7:
            std::cin >> NEw;
            weekDay = NEw;
            break;
        case 8:
            std::cin >> NEw;
            session = NEw;
            break;
        }
    }
    // save course ID to textfile
    fout.open("../Data/SchoolYear/" + curSchoolYear->year + "/Sem" + std::to_string(curSemester->getSem()) + "/course.txt", std::ios::trunc);
    if (!fout.is_open())
        std::cout << "Open unsuccessfully";
    else
    {
        for (course* tmp = curSemester->pHeadCourse; tmp; tmp=tmp->pNext)
        {
            fout << tmp->id << std::endl;
        }
    }
    fout.close();
    std::string sem = std::to_string(curSemester->getSem());
    std::string wd = std::to_string (weekDay);
    curSemester->saveCoursetoFolder(name, id, className, lecturer, credit, maxStudent, wd, session, curSchoolYear->year, sem);// function call
}

void course::addStudentMenu()
{
    int choice;
    do
    {
        system("cls");
        drawHeader();
        drawBox(mid - 53 / 2, 8, 53, 5);
        
        gotoxy(mid - 49 / 2, 9); std::cout << "1. Add student manually\n";
        gotox(mid - 49 / 2); std::cout << "2. Import csv file\n"; //chua lam
        gotox(mid - 49 / 2); std::cout << "0. Back\n\n";
        gotox(mid - 49 / 2); std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (choice <= 0 || choice > 2) {
            std::cout << "\n"; gotox(mid - 24 / 2);
            SetColor(7, 4); std::cout << "Please input correctly!"; SetColor(7, 0);

            Sleep(1000);

            //Reset
            gotox(mid - 24 / 2); std::cout << "                       ";
            gotoxy(mid - 9 / 2, -2); std::cout << "               ";
            gotox(mid - 9 / 2);
        }
        else addStudent(choice);
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
            //header
            drawHeader();

            std::cout << "\n"; gotox(mid - 49 / 2);
            std::cout << "Id:";
            std::cin.ignore();
            getline(std::cin, id);

            gotox(mid - 49 / 2); std::cout << "First name:";
            getline(std::cin, firstname);

            gotox(mid - 49 / 2); std::cout << "Last name:";
            getline(std::cin, lastname);

            gotox(mid - 49 / 2); std::cout << "Gender:";
            std::cin >> gender;

            gotox(mid - 49 / 2); std::cout << "Date of birth(dd/mm/yyyy):";
            std::cin.ignore();
            getline(std::cin, dob);

            gotox(mid - 49 / 2); std::cout << "Social id:";
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

            std::cout << "\n"; gotox(mid - 48 / 2);
            loadingPage();
            gotox(mid - 27 / 2); std::cout << "                            ";
            gotoxy(mid - 10 / 2, -2); std::cout << "         ";
            
            SetColor(7, 2); gotox(mid - 26 / 2);
            std::cout << "Add student successfully!";
            SetColor(7, 0);

            //Reset
            gotox(mid - 26 / 2); std::cout << "                         ";
            gotoxy(mid - 49 / 2, -1);

            std::cout << "Do you want to add more (Y/y to continue N/n to stop): ";
            std::cin >> ch;
        }
        else
        {
            system("cls");
            //header
            drawHeader();
            
            std::cout << "\n"; gotox(mid - 49 / 2);
            std::cout << "Input the directory:";
            std::string dir;
            std::cin.ignore();
            getline(std::cin, dir);

            std::cout << "\n";
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
                            gotox(mid - 49 / 2);
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

            std::cout << "\n"; gotox(mid - 26 / 2);
            SetColor(7, 4); std::cout << "Add student successfully!"; SetColor(7, 0);
            Sleep(1000);

            //Reset
            gotox(mid - 26 / 2); std::cout << "                         ";
            gotox(mid - 28 / 2);

            std::cout << "Press any key to go back...";
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
    drawHeader();
    if (!pHeadStudent) {
        std::cout << "\n"; gotox(mid - 38 / 2);
        SetColor(7, 4); std::cout << "There are no students in this course!"; SetColor(7, 0);

        Sleep(1000);
        return;
    }

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
    //header
    drawHeader();
    std::cout << "\n"; gotox(mid - 16 / 2);
    SetColor(7, 9);
    std::cout << "Information of Course\n\n";
    SetColor(7, 0);

    gotox(mid - 49 / 2);
    std::cout << "1.Id:" << id << std::endl;

    gotox(mid - 49 / 2);
    std::cout << "2.Name:" << name << std::endl;

    gotox(mid - 49 / 2);
    std::cout << "3.Class name:" << className << std::endl;

    gotox(mid - 49 / 2);
    std::cout << "4.Lecturer:" << lecturer << std::endl;

    gotox(mid - 49 / 2);
    std::cout << "5.Credit:" << credit << std::endl;

    gotox(mid - 49 / 2);
    std::cout << "6.Max student:" << maxStudent << std::endl;

    gotox(mid - 49 / 2);
    std::cout << "7.Day performed per week:" << weekDay << std::endl;

    gotox(mid - 49 / 2);
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

    std::cout << "\n"; gotox(mid - 23 / 2);
    SetColor(7, 2);
    std::cout << "Press any key to back:";
    SetColor(7, 0);

    drawBox(mid - 53 / 2, 9, 53, 9);
    _getch();
}
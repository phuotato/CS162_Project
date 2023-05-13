#include "Course.h"
#include "schoolYear.h"
#include "Semester.h"
#include "Graphic.h"
#include <fstream>
#include <direct.h>
#include <string>
#include "Student.h"
#include "Display.h"

//global variable
extern schoolYear* pHeadSchoolYear;
extern schoolYear* curSchoolYear;
extern semester* curSemester;
extern course* curCourse;
extern int mid;

//Constructor
bool isValidWeekday(const std::string& weekday)
{
    static const std::string validWeekdays[] = { "MON", "TUE", "WED", "THU", "FRI", "SAT" };
    static const int numValidWeekdays = sizeof(validWeekdays) / sizeof(validWeekdays[0]);

    for (int i = 0; i < numValidWeekdays; i++) {
        if (weekday == validWeekdays[i]) {
            return true;
        }
    }
    return false;
}


course::course(std::string id, std::string name, std::string className, std::string lecturer, int credit, int maxStudent, std::string weekDay, int session)
{
    this->id = id;
    this->name = name;
    this->className = className;
    this->lecturer = lecturer;
    this->credit = credit;
    this->maxStudent = maxStudent;
    if (isValidWeekday(weekDay)) {
        this->weekDay = weekDay;
    }
    else {
        //invalid
        this->weekDay = "";
        std::cerr << "Error: Invalid weekday provided for course " << id << std::endl;
    }
    this->session = session;
}

void course::LoadScoreList()
{
    curCourse = curSemester->pHeadCourse;
    for (curCourse; curCourse; curCourse = curCourse->pNext)
    {
        std::ifstream read("../Data/SchoolYear/" + curSchoolYear->year + "/Sem" + std::to_string(curSemester->sem) + "/" + curCourse->id + "/score.csv");
        if (!read)
            continue;
        studentScore* curScore = curCourse->hScore;
        std::string line;
        std::getline(read, line);
        while (getline(read, line)) //ignore the first line of the CSV
        {
            // Finding comma
            int pos1 = line.find(',');           int pos2 = line.find(',', pos1 + 1);
            int pos3 = line.find(',', pos2 + 1); int pos4 = line.find(',', pos3 + 1);
            int pos5 = line.find(',', pos4 + 1); int pos6 = line.find(',', pos5 + 1);
            int pos7 = line.rfind(',');

            // get content 
            studentScore* newScore = new studentScore;
            newScore->studentID = line.substr(pos1 + 1, pos2 - pos1 - 1);
            newScore->firstName = line.substr(pos2 + 1, pos3 - pos2 - 1);
            newScore->lastName = line.substr(pos3 + 1, pos4 - pos3 - 1);
            newScore->totalMark = stod(line.substr(pos4 + 1, pos5 - pos4 - 1));
            newScore->finalMark = stod(line.substr(pos5 + 1, pos6 - pos5 - 1));
            newScore->midtermMark = stod(line.substr(pos6 + 1, pos7 - pos6 - 1));
            newScore->otherMark = stod(line.substr(pos7 + 1));
            newScore->pNext = nullptr;

            if (curCourse->hScore == nullptr)
            {
                curCourse->hScore = newScore;
                curScore = newScore;
            }
            else
            {
                curScore->pNext = newScore;
                curScore = curScore->pNext;
            }
        }
        read.close();
    }
}
void course::ExportClass()
{
    std::ofstream fout;
    std::string courseID = curCourse->id;
    if (!curCourse->pHeadStudent)
        curCourse->loadStudentInCourse();
    fout.open("../InputFile/" + courseID + "_student.csv");
    //File header
    fout << "No,Student ID,First name,Last name,Total,Final,Midterm,Other" << "\n";

    int i = 1;
    student* current = curCourse->pHeadStudent;
    while (current) 
    {
        fout << i++ << ",";
        fout << current->getStudentID() << ",";
        fout << current->getFirstName() << ",";
        fout << current->getLastName() << ",";
        fout << "\n";
        current = current->pNext;
    }

    fout.close();
    gotoxy(mid - 52 / 2, 17);
    std::cout << "Finished exporting to " << id << "_scoreboard.csv\n";
    gotoxy(mid - 52 / 2, 18);
    system("pause");
    system("cls");
}

void course::ImportScoreboard()
{
    gotoxy(mid - 55 /2, 3);
    std::cout << "Format of the file address: ../CourseID_scoreboard.csv" << "\n";
    gotoxy(mid - 55 / 2, 4);
    std::cout << "For example: D:/Data/Score/PH212_22CTT2_scoreboard.csv \n\n";
    gotoxy(mid - 85 / 2, 8);
    std::cout << "Input the address of the scoreboard: ";
    std::string direct;
    std::getline(std::cin, direct);
    std::ifstream fin(direct);

    if (!fin)
    {
        gotoxy(mid - 55 / 2, 10);
        std::cout << "Error loading file! Please try again.";
        gotoxy(mid - 55 / 2, 11);
        system("pause");
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
        gotoxy(mid - 55 / 2, 10);
        std::cout << "This semester doesn't have this course!\n";
        gotoxy(mid - 55 / 2, 11);
        system("pause");
        return;
    }
    int line = 2;  
    int coorY = 12;
    while (!fin.eof())
    {
        std::string getNo,studentID, firstName, lastName, totalMarkStr, finalMarkStr, midtermMarkStr, otherMarkStr;
        double totalMark, finalMark, midtermMark, otherMark;
        std::getline(fin, getNo, ',');
        std::getline(fin, studentID, ',');
        if (studentID.empty() || fin.eof()) // check if we have reached the end of the file
            break;
        
        // get information from the file
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
            gotoxy(mid - 55 / 2, coorY);
            ++coorY;
            std::cout << "Error in line " << line << ": Invalid data format in file. Please check again.\n";
            ++line;
            continue;
        }
        if (totalMark > 10 || totalMark < 0 || finalMark > 10 || finalMark < 0 || midtermMark > 10 || midtermMark < 0 || otherMark > 10 || otherMark < 0)
        {
            gotoxy(mid - 55 / 2, coorY);
            ++coorY;
            std::cout << "Error in line " << line << ": Invalid data format in file!" << "\n";
            ++line;
            continue;
        }
        studentScore* newScore = new studentScore{ studentID, firstName, lastName, totalMark, finalMark, midtermMark, otherMark, nullptr };
        if (!curCourse->hScore)
        {
            curCourse->hScore = newScore;
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
    gotoxy(mid - 55 / 2, coorY + 3);
    std::cout << "Import successful!\n";
    gotoxy(mid - 55 / 2, coorY + 4);
    system("pause");
    system("cls");
}

void course::updateStudentResult()
{
    std::string studentID;
    std::cout << "Enter student ID: ";
    getline(std::cin, studentID, '\n');
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
        if (ID == curCourse->id)
        {
            write << pCur->totalMark << "," << pCur->finalMark << "," << pCur->midtermMark << "," << pCur->otherMark << "," << curCourse->id << "," << curCourse->credit << "\n";
            break;
        }
    }
    read.close();
    write.close();

    // update score.csv
    std::ofstream writeScore("../Data/SchoolYear/" + curSchoolYear->year + "/Sem" + std::to_string(curSemester->sem) + "/" + curCourse->id+ "/score.csv");
    std::ifstream readScore("../Data/SchoolYear/" + curSchoolYear->year + "/Sem" + std::to_string(curSemester->sem) + "/" + curCourse->id + "/score.csv");
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
            writeScore << temp.substr(0, pos1) << "," << temp.substr(pos1 + 1, pos2 - pos1 - 1) << ","
                << temp.substr(pos2 + 1, pos3 - pos2 - 1) << "," << temp.substr(pos3 + 1, pos4 - pos3 - 1) << ","
                << pCur->totalMark << "," << pCur->finalMark << "," << pCur->midtermMark << "," << pCur->otherMark << "\n";
            break;
        }
    }
    readScore.close();
    writeScore.close();
}


void course::ViewScoreboard() {

    // Get the number of students
    int numStudents = 0;
    studentScore* currScore = curCourse->hScore;
    while (currScore != nullptr) {
        numStudents++;
        currScore = currScore->pNext;
    }
    system("cls");
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

    int row = 5;
    int no = 1;
    currScore = curCourse->hScore;

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
        currScore = currScore->pNext;
    }

    // Draw a box around the bottom of the scoreboard
    drawBox(2, row, 90, 3);
    system("pause");
}
bool course::checkExistScoringFile(std::string direct)
{
    std::ifstream read(direct);
    if (!read){
        read.close();
        return false;
    }
    else{
        read.close();
        return true;
    }
}
void course::saveIndividualScore(course* curCourse) {
    studentScore* currScore = curCourse->hScore;
    while (currScore != nullptr) {
        std::string direct = "../Data/SchoolYear/" + curSchoolYear->year + "/Sem" + std::to_string(curSemester->sem) + "/" + currScore->studentID + ".csv";
        std::ofstream fout(direct, std::fstream::app);
        if (!checkExistScoringFile(direct))
            fout << "Total,Final,Midterm,Other,ID_Course,Credit\n";
        fout << currScore->totalMark << "," 
            << currScore->finalMark << ","
            << currScore->midtermMark << ","
            << currScore->otherMark << "," << curCourse->id << "," << curCourse->credit << "\n";
        fout.close();
        currScore = currScore->pNext;
    }
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
    curSemester->saveCoursetoFolder(name, id, className, lecturer, credit, maxStudent, weekDay, session, curSchoolYear->year, sem);// function call
}

void course::addStudentMenu()
{
    int choice = 0;
    std::string* content = new std::string[3];
    content[0] = "1. Add student manually";
    content[1] = "2. Import csv file";
    content[2] = "0. Back";

    do
    {
        system("cls");
        drawHeader();
        drawBox(mid - 53 / 2, 8, 53, 5);
        
        gotoxy(mid - 49 / 2, 9); std::cout << "1. Add student manually\n";
        gotox(mid - 49 / 2); std::cout << "2. Import csv file\n";
        gotox(mid - 49 / 2); std::cout << "0. Back";
        choice = movingBar(mid - 51/2, 9, 9, mid+51/2, 11, 1, content);
        addStudent(choice);
    } while (choice);
}

void course::addStudent(int choice)
{
    if (!pHeadStudent)
        curCourse->loadStudentInCourse();
    char ch = 'Y';
    do
    {
        if (choice == 2)
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

            gotox(mid - 49 / 2); std::cout << "Gender (0 for male, 1 for female):";
            std::cin >> gender;

            gotox(mid - 49 / 2); std::cout << "Date of birth (dd/mm/yyyy):";
            std::cin.ignore();
            getline(std::cin, dob);

            gotox(mid - 49 / 2); std::cout << "Social ID:";
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
            std::cout << "Add student successfully!          ";
            SetColor(7, 0);

            //Reset
            gotox(mid - 26 / 2); std::cout << "                         ";
            gotoxy(mid - 49 / 2, -1);

            std::cout << "Do you want to add more: ";
            YNQuestions(mid - 30/2, 13, 30);
        }
        else if (choice == 1)
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
            if (fin.is_open())
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
                        if (!pHeadStudent)
                        {
                            pHeadStudent = new student(stoi(no), id, firstname, lastname, stoi(gender), dob, socialId);
                            pTailStudent = pHeadStudent;
                        }
                        else
                        {
                            pTailStudent->pNext = new student(stoi(no), id, firstname, lastname, stoi(gender), dob, socialId);
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
    std::string path = "../Data/SchoolYear/" + curSchoolYear->year + "/Sem" + std::to_string(curSemester->getSem()) + "/" + id + "/Student's List.csv";
    saveStudentinCourse(path);
}

int compareString(std::string c, std::string d, std::string a, std::string b)
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
    if (!pHeadStudent)
        curCourse->loadStudentInCourse();

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
    drawBox(mid - 53 / 2 + 8, 9, 53, 10);
    gotoxy(mid - 16 / 2 + 5, 8);
    SetColor(7, 9);
    std::cout << "Course Information\n\n";
    SetColor(7, 0);

    gotox(mid - 53 / 2 + 9);
    std::cout << "1. Id:" << id << std::endl;

    gotox(mid - 53 / 2 + 9);
    std::cout << "2. Name:" << name << std::endl;

    gotox(mid - 53 / 2 + 9);
    std::cout << "3. Class name:" << className << std::endl;

    gotox(mid - 53 / 2 + 9);
    std::cout << "4. Lecturer:" << lecturer << std::endl;

    gotox(mid - 53 / 2 + 9);
    std::cout << "5. Credit:" << credit << std::endl;

    gotox(mid - 53 / 2 + 9);
    std::cout << "6. Max student:" << maxStudent << std::endl;

    gotox(mid - 53 / 2 + 9);
    std::cout << "7. Schedule:" << weekDay << std::endl;

    gotox(mid - 53 / 2 + 9);
    std::cout << "8. Session:";
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
        break;
    }

    std::cout << "\n"; gotox(mid - 16 / 2 + 5);
    SetColor(7, 2);
    std::cout << "Press any key to back:";
    SetColor(7, 0);
    _getch();
}

void course::saveStudentinCourse(std::string path)
{
    std::ofstream fout(path);
    if(fout.is_open())
    {
        fout << "No,Student ID,First name,Last name,Gender,Date Of Birth,Social ID";
        for (student* tmp = pHeadStudent; tmp; tmp = tmp->pNext)
        {
            fout << std::endl;
            fout << tmp->getNo() << "," << tmp->getStudentID() << "," << tmp->getFirstName() << "," << tmp->getLastName() << "," << tmp->getGender() << "," << tmp->getDate() << "," << tmp->getSocialId();
        }
    }
    fout.close();
}

void course::loadStudentInCourse()
{
    std::string path = "../Data/SchoolYear/" + curSchoolYear->year + "/Sem" + std::to_string(curSemester->getSem()) + "/" + id + "/Student's List.csv";
    std::ifstream fin(path);
    if (fin.is_open())
    {
        std::string redundant;
        getline(fin, redundant);
        while (!fin.eof())
            {
                std::string no, id, gender, firstname, lastname, dob, socialId;
                getline(fin, no, ',');
                getline(fin, id, ',');
                getline(fin, firstname, ',');
                getline(fin, lastname, ',');
                getline(fin, gender, ',');
                getline(fin, dob, ',');
                fin.get();
                getline(fin, socialId);
                if (!pHeadStudent)
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
}

void course::showingStudentList()
{
    if (!pHeadStudent)
        curCourse->loadStudentInCourse();
    std::string displayk = "N";
    std::string* content = nullptr;
    bool EnterConfirm = 0;
    int yp = 6;
    short TH = 3;
    short range = 10;
    short Pcur = 0;
    int APages = getAllStudent() / range + 1;
    student* cur = pHeadStudent;
    if (!pTailStudent) return;
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
                showStudent(cur, range, Pcur);
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
                showPStudent(cur, range, Pcur);
                showStudent(cur, range, Pcur);
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
                    cur = pHeadStudent;
                    APages = getAllStudent() / range + 1;
                    //Draw again
                    system("cls");
                    drawBox(15, 2, 30, 23);
                    Tutorial(content);
                    showStudent(cur, range, Pcur);
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
void course::showStudent(student*& pHead, short range, short& Pcur)
{
    const int tableWidth = 62;
    const int tableX = mid + 6 - tableWidth / 2;
    const int tableY = 5;
    gotoxy((2 * tableX + 45) / 2, 3);
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
    gotoxy(tableX, tableY + 1);
    drawLine(62, tableX - 2);
    gotoxy(tableX - 3, tableY + 2 + Pcur);
    drawLine(tableWidth, tableX - 2);
    std::cout << "\n\n";
    gotox(tableX - 2);

}
void course::showPStudent(student*& pHead, short range, short& Pcur) {
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
int course::getAllStudent()
{
    int i = 0;
    for (student* cur = pHeadStudent; cur; cur = cur->pNext, i++);
    return --i;
}

void course::deleteStudent()
{
    if (!pHeadStudent)
        curCourse->loadStudentInCourse();
    bool del = 0;
    while(true)
    {
        std::cout << "Full name ID";
        for (student* cur = pHeadStudent; cur; cur = cur->pNext)
            std::cout << cur->getLastName() << " " << cur->getFirstName() << " " << cur->getStudentID() << std::endl;
        std::cout << "Enter your choice(Press enter to back)";
        std::string id;
        getline(std::cin, id);
        if (id == "")
            break;
        else
        {
            if (pHeadStudent->getStudentID() == id)
            {
                student* tmp = pHeadStudent->pNext;
                delete pHeadStudent;
                pHeadStudent = tmp;
                del = 1;
            }
            else
            {
                for (student* cur = pHeadStudent; cur->pNext; cur = cur->pNext)
                {
                    if (cur->pNext->getStudentID() == id)
                    {
                        student* tmp = pHeadStudent->pNext;
                        cur->pNext = tmp->pNext;
                        delete tmp;
                        del = 1;
                        break;
                    }
                }
            }
        }
        if (del)
        {
            std::cout << "Delete succesfully\n";
            Sleep(500);
            std::cout << "Do you want to continue:(Press Y/y to continue, N/n to stop)";
            char ch;
            std::cin >> ch;
            if (ch == 'N' || ch == 'n')
                break;
        }
        else
        {
            std::cout << "This student's id do not exist\n";
            Sleep(500);
        }
    }

    std::string path = "../Data/SchoolYear/" + curSchoolYear->year + "/Sem" + std::to_string(curSemester->getSem()) + "/" + id + "/Student's List.csv";
    saveStudentinCourse(path);
}
//void course::ChooseGPARTotal() {
//    int choice = 0;
//    std::string* content = new std::string[3];
//    content[0] = "1. Show GPA of all students";
//    content[1] = "2. Show total course's score of all students";
//    content[2] = "0. Back";
//    do {
//        drawHeader();
//        drawBox(mid - 53 / 2, 8, 53, 5);
//
//        gotoxy(mid - 28 / 2, 7); std::cout << "Show score of all students.";
//        gotoxy(mid - 49 / 2, 9); std::cout << "1. Show GPA of all students";
//        gotoxy(mid - 49 / 2, 10); std::cout << "2. Show total course's score of all students";
//        gotoxy(mid - 49 / 2, 11); std::cout << "0. Back";
//        choice = movingBar(mid - 51 / 2, 9, 9 + choice, mid + 53 / 2, 11, 1, content);
//        switch (choice)
//        {
//        case 2:
//            curSemester->pHeadCourse->showGPABoardOfClass();
//            break;
//
//        case 1:
//            curSemester->pHeadCourse->showingScoreOfClassList();
//            break;
//        case 0:
//            continue;
//        }
//    } while (choice != 0);
//    delete[] content;
//
//}
//
//void course::showScoreBoardOfClass(studentScore*& curScore, course*& cur, short range, short& Pcur) {
//    const int tableWidth = 66;
//    const int tableX = mid + 6 - tableWidth / 2;
//    const int tableY = 5;
//
//    gotoxy((2 * tableX + 51) / 2, 3);
//    std::cout << "Student's List";
//
//    // Print table header
//    gotoxy(tableX, tableY);
//    std::cout << "Course's ID   Student ID   First Name    Last Name         Total\n";
//
//    int i = tableY + 2;
//    int k = 0;
//    bool flag = 0;
//    while (cur != nullptr && k < range) {
//        for (; curScore; curScore = curScore->pNext) {
//            // Print student information in table format
//            gotoxy(tableX, i);
//            std::cout << i - tableY - 1 << ".    " << curScore->studentID << "      ";
//            gotoxy(tableX + 19, i);
//            std::cout << curScore->firstName;
//            gotoxy(tableX + 33, i);
//            std::cout << curScore->lastName;
//            gotoxy(tableX + 51, i);
//            std::cout << curScore->totalMark;
//
//            if (curScore->pNext == nullptr) {
//                flag = 1;
//            }
//            i++;
//            k++;
//            Pcur++;
//        }
//        if (flag == 1) {
//            flag = 0;
//            if (cur->pNext == nullptr) break;
//            cur = cur->pNext;
//        }
//    }
//
//    drawBox(tableX - 2, tableY - 1, tableWidth, Pcur + 6);
//    gotoxy(tableX, tableY + 1);
//    drawLine(62, tableX - 2);
//
//    gotoxy(tableX - 3, tableY + 2 + Pcur);
//    drawLine(tableWidth, tableX - 2);
//    std::cout << "\n\n";
//    gotox(tableX - 2);
//}
//
//int course::getAllScore() {
//    int i = 0;
//   
//    for (course* cur = curSemester->pHeadCourse; cur; cur = cur->pNext) {
//        for (studentScore* curScore = cur->hScore; curScore; curScore = curScore->pNext, i++);
//    }
//    return --i;
//}
//
//void course::showPScoreBoardOfClass(studentScore*& curScore, course*& cur, short range, short& Pcur) {
//    course* pHead = curSemester->pHeadCourse;
//    
//    //Check if the last page
//    if (Pcur % range == 0) {
//        for (; pHead; pHead = pHead->pNext) {
//            studentScore* pHeadScore = pHead->hScore;
//            for (int i = 0; i < Pcur - range * 2 && pHeadScore; i++, pHeadScore = pHeadScore->pNext);
//            curScore = pHeadScore;
//        }
//        cur = pHead;
//        Pcur -= range * 2;
//    }
//    else {
//        for (; pHead; pHead = pHead->pNext) {
//            studentScore* pHeadScore = pHead->hScore;
//            for (int i = 0; i < Pcur - (Pcur%range) - range && pHeadScore; i++, pHeadScore = pHeadScore->pNext);
//            curScore = pHeadScore;
//        }
//        cur = pHead;
//        Pcur -= (Pcur % range) + range;
//    }
//}
//
//void course::showingScoreOfClassList(student* pHead) {
//    std::string displayk = "N";
//    std::string* content = nullptr;
//    bool EnterConfirm = 0;
//    int yp = 6;
//    short TH = 3;
//    short range = 10;
//    short Pcur = 0;
//    int APages = getAllScore() / range + 1;
//    student* pTail = pHead;
//    student* cur = pHead;
//    if (!pTail) return;
//    for (; pTail->pNext; pTail = pTail->pNext);
//
//    system("cls");
//    while (true) {
//
//        switch (TH) {
//            //Next page
//        case 3: {
//            if (cur == nullptr) {
//                SetColor(7, 12);
//                if (Pcur % range == 0 && Pcur != 0) gotoxy(mid - 25 / 2, range + 12);
//                else gotoxy(mid - 25 / 2, Pcur % range + 12);
//                std::cout << "You are at the last page";
//                SetColor(7, 0);
//
//                Sleep(2000);
//
//                //Reset the command
//                gotox(mid - 47 / 2);
//                std::cout << "                                                          \r";
//
//            }
//            else {
//                system("cls");
//                drawBox(15, 2, 30, 23);
//                Tutorial(content);
//                showStudents(cur, range, Pcur);
//                Description(range, APages, (Pcur - 1) / range + 1, Pcur, 52, 62);
//            }
//            yp = 6;
//            break;
//        }
//              //Previous Page
//        case 2: {
//            if (Pcur <= range) {
//                SetColor(7, 12);
//                if (Pcur % range == 0 && Pcur != 0) gotoxy(mid - 25 / 2, range + 12);
//                else gotoxy(mid - 25 / 2, Pcur % range + 12);
//                std::cout << "You are at the first page";
//                SetColor(7, 0);
//
//                Sleep(2000);
//
//                //Reset the command
//                gotox(mid - 47 / 2);
//                std::cout << "                                                          \r";
//
//            }
//            else {
//                system("cls");
//                drawBox(15, 2, 30, 23);
//                Tutorial(content);
//                showPStudents(cur, range, Pcur);
//                showStudents(cur, range, Pcur);
//                Description(range, APages, (Pcur - 1) / range + 1, Pcur, 52, 62);
//            }
//            yp = 6 + 4;
//            break;
//        }
//              //Enter to confirm
//        case 0: {
//            EnterConfirm = 1;
//            break;
//        }
//              //Change list
//        case 1: {
//
//            if (Pcur % range == 0 && Pcur != 0) gotoxy(mid - 50 / 2, range + 12);
//            else gotoxy(mid - 50 / 2, Pcur % range + 12);
//            std::cout << "Please enter the number you want to change list: ";
//            getline(std::cin, displayk);
//
//            if (displayk[0] <= '9' && displayk[0] >= '0') {
//                int sample = stoi(displayk);
//                if (sample > 25 || sample < 10) {
//                    SetColor(7, 12);
//                    std::cout << "\n\n"; gotox(mid - 42 / 2);
//                    std::cout << "The range is too big or too small (10~25)!";
//                    SetColor(7, 0);
//
//                    Sleep(2000);
//
//                    //Reset the command
//                    gotox(mid - 47 / 2);
//                    std::cout << "                                                          \r";
//                    gotoxy(mid - 50 / 2, -3); std::cout << "                                                    ";
//                }
//                else {
//                    //Reset everything
//                    range = sample;
//                    Pcur = 0;
//                    cur = pHead;
//                    APages = getAllClass() / range + 1;
//
//                    //Draw again
//                    system("cls");
//                    drawBox(15, 2, 30, 23);
//                    Tutorial(content);
//                    showStudents(cur, range, Pcur);
//                    Description(range, APages, (Pcur - 1) / range + 1, Pcur, 52, 62);
//                }
//            }
//            yp = 6 + 8;
//            break;
//        }
//        }
//        if (EnterConfirm == 1) {
//            if (Pcur % range == 0 && Pcur != 0) gotoy(range + 8);
//            else gotoy(Pcur % range + 8);
//            break;
//        }
//        TH = movingBarTutorial(16, 6, yp, 44, 18, 4, content);
//    }
//}

void course::deleteStudentCourseList()
{
    for (schoolYear* cur = pHeadSchoolYear; cur; cur = cur->pNext)
    {
        for (semester* tmp = cur->pHeadSemester; tmp; tmp = tmp->pNext)
        {
            for (course* temp = tmp->pHeadCourse; temp; temp = temp->pNext)
            {
                for (student* head = temp->pHeadStudent; head;)
                {
                    student* dummy = head->pNext;
                    delete head;
                    head = dummy;
                }
            }
        }
    }
}

void course::deleteCourseList()
{
    for (schoolYear* cur = pHeadSchoolYear; cur; cur = cur->pNext)
    {
        for (semester* tmp = cur->pHeadSemester; tmp; tmp = tmp->pNext)
        {
            for (course* temp = tmp->pHeadCourse; temp;)
            {
                course* dummy=temp->pNext;
                delete temp;
                temp = dummy;
            }
        }
    }
}
//#include "Universal.h"
//#include <fstream>
//#include <sstream>

//definition of constructor
//Class::Class(char cYear[2], char cName[5], char cSubclass, Student*& headS) : Subclass(cSubclass), HeadS(headS) {
//    cout << "Please enter the year this class in: ";
//    cin.get(cYear, 2, '\n');
//    for (int i = 0; i < 2; i++) {
//        Year[i] = cYear[i];
//    }
//    cin.ignore(32000, '\n');
//
//    cout << "Please enter the program name for this class: ";
//    cin.get(cName, 5, '\n');
//    for (int i = 0; i < 5; i++) {
//        Name[i] = cName[i];
//    }
//    cin.ignore(32000, '\n');
//
//    cout << "Please enter the subclass: ";
//    cin >> cSubclass;
//    cin.ignore(32000, '\n');
//
//}

//definition of function

//void Class::Add_Student(ifstream& fin, string username, Student*& student)
//{
//    cout << "Enter your class code (Example: 22TT2, 22TT1, 21CLC06, 20VP,...):  ";
//    string classcode;
//    cin >> classcode;
//    
// 
// ("StudentProfile/" + classcode + ".csv");
//    if (!fin)
//    {
//        cout << "Error loading data! Please try again.";
//        return;
//    }
//    string redundant;
//    getline(fin, redundant);
//    while (!fin.eof())
//    {
//        Student* newStudent = new Student;
//        getline(fin, newStudent->ID, ',');
//        string getNO;
//        getline(fin, getNO, ',');
//        if (fin.eof())
//            break;
//        newStudent->No = stoi(getNO);
//        getline(fin, newStudent->firstname, ',');
//        getline(fin, newStudent->lastname, ',');
//        string getGender;
//        getline(fin, getGender, ',');
//        newStudent->Gender = stoi(getGender);
//        string getDay, getMonth, getYear;
//        getline(fin, getDay, '/');
//        getline(fin, getMonth, '/');
//        getline(fin, getYear, ',');
//        newStudent->DOB.day = stoi(getDay);
//        newStudent->DOB.month = stoi(getMonth);
//        newStudent->DOB.year = stoi(getYear);
//        fin.ignore();
//        getline(fin, newStudent->Social_ID);
//        newStudent->pNext = student;
//        student = newStudent;
//    }
//}

//day chi la vi du
//void addStudentUsingsstream(const string& fileName, Student*& headS) {
//    ifstream fin(fileName);
//    if (!fin) {
//        cout << "Error loading data! Please try again.";
//        return;
//    }
//
//    string line;
//    while (getline(fin, line)) {
//        istringstream iss(line);
//        int no;
//        string id, firstname, lastname, socialId;
//        bool gender;
//        Date dob;
//
//        if (!(iss >> no >> id >> firstname >> lastname >> gender >> dob.day >> dob.month >> dob.year >> socialId)) {
//            cout << "Error reading line from file";
//            continue;
//        }
//
//        Student* newStudent = new Student(no, id, firstname, lastname, gender, dob, socialId);
//        newStudent->pNext = headS;
//        headS = newStudent;
//    }
//}
//
//void Class::deleteStudentList(Student*& student)
//{
//    Student* cur = student;
//    while (cur != nullptr)
//    {
//        Student* temp = cur;
//        cur = cur->pNext;
//        delete temp;
//    }
//}
#include <iostream>
#include <fstream>
#include "Login.h"
using namespace std;
typedef void type;

type Staff()
{
	ifstream fin;
	system("cls");
	string folder = "../StaffAccount/";
	login(folder);
	system("cls");
	cout << "Begin of school year: \n";
	// goi cac function Create a school year, classes, Add students o dayID
}

type Student()
{
	system("cls");
	cout << "Select option: \n";

}

int main()
{
	drawBox();
	Staff();
	return 0;
}
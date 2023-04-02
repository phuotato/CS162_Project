#include <iostream>
#include "Login.h"
using namespace std;
typedef void type;

type Staff()
{
	system("cls");
	login();
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
	int x;
	cout << "Welcome to FIT.HCMUS Management System. \n";
	cout << "Are you a \n";
	cout << "(1)Staff or (2)Student?:";
	cin >> x;
	if (x == 1) Staff();
	else Student();
	return 0;
}
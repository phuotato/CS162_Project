#include <iostream>
using namespace std;
typedef void type;

type Staff()
{
	system("cls");
	cout << "Begin of school year: \n";
	// goi cac function Create a school year, classes, Add students o dayID
}

type Student()
{
	system("cls");
	cout << "Select option: ";

}

int main()
{
	int x;
	cout << "(1)Staff or (2)Student?:";
	cin >> x;
	if (x == 1) Staff();
	else Student();
	
	return 0;
}
#include "WelcomePage.h"
using namespace std;

string username{};

void welcomePage()
{
    // set console size and title
    system("mode con: cols=90 lines=30");
    SetConsoleTitle(TEXT("FIT.HCMUS Management Program"));
	system("color 70");
    //header
    drawHeader();
    
    //welcome message
    //setColor(0); // black text color
    cout << "\n\n\n\n";
    drawBox(20, 10, 40, 8);
    gotoxy(32, 12);
    cout << "Welcome to";
    gotoxy(25, 14);
	//system("color 79");
    //setColor(9); // light blue text color
    cout << "FIT.HCMUS Management System.";
    //setColor(15);

    // wait for user input to continue
    gotoxy(28, 24);
    cout << "Press any key to continue...";
    cin.get();

    // clear screen and display menu
    system("cls");
    cout << "\n\n\n\n";
    drawBox(20, 7, 35, 10);
    gotoxy(32, 8);
    cout << "Login as";
    gotoxy(25, 10);
    cout << "1. Staff";
    gotoxy(25, 12);
    cout << "2. Student";
    gotoxy(25, 14);
    cout << "0. Exit";
	
	gotoxy(25, 17);
	cout << "Your choice: ";
	int option;
	cin >> option;
	switch (option) {
	case 1: 
		Staff();
		break;
	case 2:
		login("../StudentAccount/");
		break;
	case 0: 
		exit(0);
		break;
	default: 
		cout << "Invalid input.";
	}
		
}

void loginPage()
{
	//system("cls");
	drawHeader();
	char ch;
	gotoxy(20, 11);
	cout << "Username:";
	gotoxy(20, 16);
	cout << "Password:";
	for (int i = 0; i < 30; ++i)
	{
		ch = char(196);
		gotoxy(i + 30, 10);
		cout << ch;
		gotoxy(i + 30, 12);
		cout << ch;
	}
	gotoxy(59, 10);
	ch = char(191);
	cout << ch;
	gotoxy(59, 12);
	ch = char(217);
	cout << ch;
	gotoxy(30, 10);
	ch = char(218);
	cout << ch;
	gotoxy(30, 12);
	ch = char(192);
	cout << ch;
	for (int i = 0; i < 1; ++i)
	{
		ch = char(179);
		gotoxy(59, 11 + i);
		cout << ch;
		gotoxy(30, 11 + i);
		cout << ch;
	}
	for (int i = 0; i < 30; ++i)
	{
		ch = char(196);
		gotoxy(i + 30, 15);
		cout << ch;
		gotoxy(i + 30, 17);
		cout << ch;
	}
	gotoxy(59, 15);
	ch = char(191);
	cout << ch;
	gotoxy(59, 17);
	ch = char(217);
	cout << ch;
	gotoxy(30, 15);
	ch = char(218);
	cout << ch;
	gotoxy(30, 17);
	ch = char(192);
	cout << ch;
	for (int i = 0; i < 1; ++i)
	{
		ch = char(179);
		gotoxy(59, 16 + i);
		cout << ch;
		gotoxy(30, 16 + i);
		cout << ch;
	}
}


void login(string folder)
{
	while (true)
	{
		ifstream fin;
		bool flag = 0;
		loginPage();
		string password{};
		gotoxy(31, 11);
		setcursor(1, 10);
		getline(cin, username);
		gotoxy(31, 16);
		char key;
		key = _getch();
		gotoxy(31, 16);
		while (key != 13)
		{
			if (key == 8)
			{
				if (!password.empty())
					password.pop_back();
				HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
				COORD current = GetConsoleCursorPosition(h);
				if (current.X != 31 && current.Y != 17)
					cout << '\b' << " " << '\b';
			}
			else
			{
				cout << "*";
				password += key;
			}
			key = _getch();
		}
		gotoxy(31, 16);
		cout << password;
		gotoxy(31, 19);
		cout << "                                                        ";
		gotoxy(31, 19);
		cout << "Press enter to sign in:";
		setcursor(0, 0);
		cin.get();


		if (username == "" || password == "")
		{
			system("cls");
			gotoxy(31, 19);
			cout << "Invalid username or password\n";
			continue;
		}
		fin.open(folder + username + ".txt", ios::in);
		string check_username, check_password;
		fin >> check_username;
		fin >> check_password;
		fin.close();
		if (check_username != username || check_password != password)
		{
			gotoxy(31, 19);
			cout << "                                                      ";
			system("cls");
			gotoxy(31, 19);
			cout << "Your password or username wrong!\n";
			gotoxy(31, 20);
			continue;
		}
		gotoxy(31, 19);
		cout << "                                                       ";
		gotoxy(31, 19);
		cout << "Sign in successfully\n";
		setcursor(0, 0);
		Sleep(300);
		return;
	}
}
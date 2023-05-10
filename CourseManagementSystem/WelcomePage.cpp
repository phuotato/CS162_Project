#include "WelcomePage.h"
#include "Graphic.h"
#include "Universal.h"
#include "Staff.h"
#include "StudentAcc.h"
std::string username{};
extern int mid;

void welcomePage()
{
    // set console size and title
    system("mode con: cols=156 lines=50");
	mid = getMidColumns();
    SetConsoleTitle(TEXT("FIT.HCMUS Management Program"));
	system("color 70");
    //header
    drawHeader();
    
    //welcome message
    std::cout << "\n\n\n\n";
    drawBox(mid-40/2, 10, 40, 7);
    gotoxy(mid-10/2, 12);
    std::cout << "Welcome to";
    gotoxy(mid-28/2, 14);
	SetColor(7, 1);

    std::cout << "FIT.HCMUS Management System.";
	SetColor(7, 0);
    // wait for user input to continue
    gotoxy(mid-28/2, 24);
    std::cout << "Press any key to continue...";
	std::cin.get();

    // clear screen and display menu
    system("cls");
    std::cout << "\n\n\n\n";
	drawBox(mid - 35 / 2, 8, 35, 9);
    gotoxy(mid-8/2, 6);
    std::cout << "Login as";
    gotoxy(mid-26/2, 10);
    std::cout << "1. Staff";
    gotoxy(mid-26/2, 12);
    std::cout << "2. Student";
    gotoxy(mid-26/2, 14);
    std::cout << "0. Exit"; //character i make the box break
	
	gotoxy(mid-26/2, 17);
	std::cout << "Your choice: ";
	int option;
	std::cin >> option;
	switch (option) {
	case 1: 
		std::cin.get();
		system("cls");
		//login("../StaffAccount/");
		Staff();
		break;
	case 2:
		std::cin.get();
		system("cls");
		login("../StudentAccount/");
		StudentAcc();
		break;
	case 0: 
		exit(0);
		break;
	default: 
		std::cout << "Invalid input.";
	}
		
}

void loginPage()
{
	//system("cls");
	drawHeader();
	char ch;
	gotoxy(20, 11);
	std::cout << "Username:";
	gotoxy(20, 16);
	std::cout << "Password:";
	for (int i = 0; i < 30; ++i)
	{
		ch = char(196);
		gotoxy(i + 30, 10);
		std::cout << ch;
		gotoxy(i + 30, 12);
		std::cout << ch;
	}
	gotoxy(59, 10);
	ch = char(191);
	std::cout << ch;
	gotoxy(59, 12);
	ch = char(217);
	std::cout << ch;
	gotoxy(30, 10);
	ch = char(218);
	std::cout << ch;
	gotoxy(30, 12);
	ch = char(192);
	std::cout << ch;
	for (int i = 0; i < 1; ++i)
	{
		ch = char(179);
		gotoxy(59, 11 + i);
		std::cout << ch;
		gotoxy(30, 11 + i);
		std::cout << ch;
	}
	for (int i = 0; i < 30; ++i)
	{
		ch = char(196);
		gotoxy(i + 30, 15);
		std::cout << ch;
		gotoxy(i + 30, 17);
		std::cout << ch;
	}
	gotoxy(59, 15);
	ch = char(191);
	std::cout << ch;
	gotoxy(59, 17);
	ch = char(217);
	std::cout << ch;
	gotoxy(30, 15);
	ch = char(218);
	std::cout << ch;
	gotoxy(30, 17);
	ch = char(192);
	std::cout << ch;
	for (int i = 0; i < 1; ++i)
	{
		ch = char(179);
		gotoxy(59, 16 + i);
		std::cout << ch;
		gotoxy(30, 16 + i);
		std::cout << ch;
	}
}


void login(std::string folder)
{
	while (true)
	{
		std::ifstream fin;
		bool flag = 0;
		loginPage();
		std::string password{};
		gotoxy(31, 11);
		setcursor(1, 10);
		getline(std::cin, username);
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
					std::cout << '\b' << " " << '\b';
			}
			else
			{
				std::cout << "*";
				password += key;
			}
			key = _getch();
		}
		gotoxy(31, 16);
		std::cout << password;
		gotoxy(31, 19);
		std::cout << "                                                        ";
		gotoxy(31, 19);
		std::cout << "Press enter to sign in:";
		setcursor(0, 0);
		std::cin.get();


		if (username == "" || password == "")
		{
			system("cls");
			gotoxy(31, 19);
			std::cout << "Invalid username or password\n";
			continue;
		}
		fin.open(folder + username + ".txt", std::ios::in);
		std::string check_username, check_password;
		fin >> check_username;
		fin >> check_password;
		fin.close();
		if (check_username != username || check_password != password)
		{
			gotoxy(31, 19);
			std::cout << "                                                      ";
			system("cls");
			gotoxy(31, 19);
			std::cout << "Your password or username wrong!\n";
			gotoxy(31, 20);
			continue;
		}
		gotoxy(31, 19);
		std::cout << "                                                       ";
		gotoxy(31, 19);
		std::cout << "Sign in successfully\n";
		setcursor(0, 0);
		Sleep(300);
		return;
	}
}
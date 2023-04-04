#include "Login.h"
void gotoxy(short a, short b)
{
	COORD coordinates{};
	coordinates.X = a;
	coordinates.Y = b;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void drawBox()
{
	gotoxy(20, 5); cout << " ____  ____  ____  __  _   _  ___  __  __  __  __  ___ " << "\n";
	gotoxy(20, 6); cout << "( ___)(_  _)(_  _)/  \\( )_( )/ __)(  \\/  )(  )(  )/ __)" << "\n";
	gotoxy(20, 7); cout << " )__)  _)(_   )( | ()/ ) _ (( (__  )    (  )(__)( \\__ \\" << "\n";
	gotoxy(20, 8); cout << "(__)  (____) (__) \\__ (_) (_)\\___)(_/\\/\\_)(______)(___/" << "\n";
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
	ifstream fin;
	bool flag = 0;
	drawBox();
	string username{}, password{};
	gotoxy(31, 11);
	getline(cin, username);
	fin.open(folder + username + ".txt", ios::in);
	string check_username, check_password;
	fin >> check_username;
	fin >> check_password;
	fin.close();
	gotoxy(31, 16);
	char key;
	key = _getch();
	gotoxy(31, 18);
	cout << "Press enter to unhide password";
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
	cout << "                            ";
	gotoxy(31, 19);
	cout << "Press enter to sign in:";
	cin.get();
	if (check_password != password)
	{
		flag = 1;
		gotoxy(31, 19);
		cout << "Your password or username wrong!";
		gotoxy(31, 20);
		system("pause");
		system("cls");
	}
	if (flag == 0)
	{
		gotoxy(31, 19);
		cout << "                        ";
		gotoxy(31, 19);
		cout << "Signin succesfully\n";
		return;

	}
	while (true)
	{
		drawBox();
		string username{}, password{};
		gotoxy(31, 11);
		getline(cin, username);
		fin.open( folder + username + ".txt", ios::in);
		string check_username, check_password;
		fin >> check_username;
		fin >> check_password;
		fin.close();
		gotoxy(31, 16);
		char key;
		key = _getch();
		gotoxy(31, 18);
		cout << "Press enter to unhide password";
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
		cout << "                                              ";
		gotoxy(31, 19);
		cout << "Press enter to sign in:";
		cin.get();
		if (check_password != password)
		{
			gotoxy(31, 19);
			cout << "Your password or username wrong!";
			gotoxy(31, 20);
			system("pause");
			system("cls");
		}
		else
			break;
	}
	gotoxy(31, 19);
	cout << "                        ";
	gotoxy(31, 19);
	cout << "Signin succesfully\n";
}
COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		// The function failed. Call GetLastError() for details.
		COORD invalid = { 0, 0 };
		return invalid;
	}
}
#include "WelcomePage.h"
#include "Graphic.h"
#include "Universal.h"
#include "Staff.h"
#include "StudentAcc.h"
#include "Display.h"
extern std::string username{};
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
	system("pause");

    // clear screen and display menu
    system("cls");
    std::cout << "\n\n\n\n";
	drawBox(mid - 35 / 2, 8, 35, 9);
    gotoxy(mid-8/2, 6);
    SetColor(7, 9);
    std::cout << "Login as";
    SetColor(7, 0);
    gotoxy(mid-26/2, 10);
    std::cout << "1. Staff";
    gotoxy(mid-26/2, 12);
    std::cout << "2. Student";
    gotoxy(mid-26/2, 14);
    std::cout << "0. Exit"; //character i make the box break

    std::string* content = new std::string[3];

    content[0] = "  1. Staff";
    content[1] = "  2. Student";
    content[2] = "  0. Exit";

	int option;
	option = movingBar(mid-32/2, 10, 10, mid+32/2, 14, 2, content);
	switch (option) {
	case 2:
		system("cls");
        
		Staff();
		break;
	case 1:
		system("cls");
        login("../StudentAccount/");
		StudentAcc();
		break;
	case 0:
		exit(0);
		break;
	default:
		std::cout << "\n\nInvalid input.\n";
	}
		
}


void loginPage()
{
	drawHeader();
	int mid = getMidColumns();
	int x = mid - 20;
	int y = 11;

	// Draw username label
	gotoxy(x, y);
	std::cout << "Username:";

	// Draw username input box
	drawBox(x + 11, y - 1, 30, 3);

	// Draw password label
	gotoxy(x, y + 5);
	std::cout << "Password:";

	// Draw password input box
	drawBox(x + 11, y + 4, 30, 3);
}

void login(std::string folder)
{
    int mid = getMidColumns();
    int x = mid - 8;
    int y = 11;

    while (true)
    {
        std::ifstream fin;
        bool flag = false;
        loginPage();
        std::string password{};
        gotoxy(x, y);
        setcursor(1, 10);
        getline(std::cin, username);
        gotoxy(x, y + 5);
        char key;
        key = _getch();
        gotoxy(x, y + 5);

        while (key != 13)
        {
            if (key == 8)
            {
                if (!password.empty())
                    password.pop_back();
                HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
                COORD current = GetConsoleCursorPosition(h);
                if (current.X != x && current.Y != y + 5)
                    std::cout << '\b' << " " << '\b';
            }
            else
            {
                std::cout << "*";
                password += key;
            }
            key = _getch();
        }

        gotoxy(x, y + 5);
        std::cout << password;
        gotoxy(x, y + 8);
        std::cout << "                                                        ";
        gotoxy(x, y + 8);
        std::cout << "Press enter to sign in:";
        setcursor(0, 0);
        std::cin.get();

        if (username.empty() || password.empty())
        {
            system("cls");
            gotoxy(x, y + 8);
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
            gotoxy(x, y + 8);
            std::cout << "                                                      ";
            system("cls");
            gotoxy(x, y + 8);
            std::cout << "Your password or username is wrong!\n";
            gotoxy(x, y + 9);
            continue;
        }

        gotoxy(x, y + 8);
        std::cout << "                                                       ";
        gotoxy(x, y + 8);
        std::cout << "Sign in successfully\n";
        setcursor(0, 0);
        Sleep(300);
        return;
    }
}





#include "ChangePassword.h"
extern string username;
void changePassword(ifstream& fin, ofstream& fout)
{
	if (username[0] >= 'a' && username[0] <= 'z')
		fin.open("../StaffAccount/" + username + ".txt", ios::in);
	else if (username[0] >= '0' && username[0] <= '9')
		fin.open("../StudentAccount/" + username + ".txt", ios::in);
	if (!fin)
	{
		std::cout << "Account Not Found! Please try again." << std::endl << std::endl;
		std::cout << "Process done! The system will go back to the menu." << std::endl;
		system("pause");
		return;
	}
	std::cout << "Input the password: ";
	string password, newPass, confirmPass;
	cin >> password;
	string check_username, check_password;
	fin >> check_username;
	fin >> check_password;
	bool condition = false;
	fin.close();																			//Remember to close text file
	while (condition == false)
	{
		if (check_username == username && check_password == password)
		{
			std::cout << "Enter the new password: ";
			cin >> newPass;
			std::cout << "Confirm your password: ";
			cin >> confirmPass;
			if (newPass == confirmPass)
			{
				if (username[0] >= 'a' && username[0] <= 'z')
					fout.open("../StaffAccount/" + username + ".txt", ios::trunc);
				else if (username[0] >= '0' && username[0] <= '9')
					fout.open("../StudentAccount/" + username + ".txt", ios::trunc);
				fout << username << std::endl;
				fout << newPass;
				condition = true;
				std::cout << "Change password successfully!" << std::endl;
				fout.close();																//Remember to close text file
			}
			else
			{
				std::cout << "Wrong password. Please input again.";
			}
		}
		else
		{
			std::cout << "Wrong password. Please try again" << std::endl;
			std::cout << "Input the password: ";
			cin >> password;
		}
	}
	std::cout << std::endl;
	std::cout << "Process done! The system will go back to the menu.";
	system("pause");
}
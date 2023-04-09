#include "ChangePassword.h"
extern std::string username;
void changePassword(std::ifstream& fin, std::ofstream& fout)
{
	if (username[0] >= 'a' && username[0] <= 'z')
		fin.open("../StaffAccount/" + username + ".txt", std::ios::in);
	else if (username[0] >= '0' && username[0] <= '9')
		fin.open("../StudentAccount/" + username + ".txt", std::ios::in);
	if (!fin)
	{
		std::cout << "Account Not Found! Please try again." << std::endl << std::endl;
		std::cout << "Process done! The system will go back to the menu." << std::endl;
		system("pause");
		return;
	}
	std::cout << "Input the password: ";
	std::string password, newPass, confirmPass;
	std::cin >> password;
	std::string check_username, check_password;
	fin >> check_username;
	fin >> check_password;
	bool condition = false;
	fin.close();																			//Remember to close text file
	while (condition == false)
	{
		if (check_username == username && check_password == password)
		{
			std::cout << "Enter the new password: ";
			std::cin >> newPass;
			std::cout << "Confirm your password: ";
			std::cin >> confirmPass;
			if (newPass == confirmPass)
			{
				if (username[0] >= 'a' && username[0] <= 'z')
					fout.open("../StaffAccount/" + username + ".txt", std::ios::trunc);
				else if (username[0] >= '0' && username[0] <= '9')
					fout.open("../StudentAccount/" + username + ".txt", std::ios::trunc);
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
			std::cin >> password;
		}
	}
	std::cout << std::endl;
	std::cout << "Process done! The system will go back to the menu.";
	system("pause");
}
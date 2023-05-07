#include "ChangePassword.h"
#include "Graphic.h"
extern int mid;
extern std::string username;

void changePassword(std::ifstream& fin, std::ofstream& fout)
{
	if (username[0] >= 'a' && username[0] <= 'z')
		fin.open("../StaffAccount/" + username + ".txt", std::ios::in);
	else if (username[0] >= '0' && username[0] <= '9')
		fin.open("../StudentAccount/" + username + ".txt", std::ios::in);
	//if login successfully, do we need to check this???
	if (!fin)
	{
		std::cout << "Account Not Found! Please try again." << std::endl << std::endl;
		std::cout << "Process done! The system will go back to the menu." << std::endl;
		system("pause");
		return;
	}
	std::cout << "\n"; gotox(mid - 53 / 2);
	std::cout << "Input the password (Press enter to go back): ";
	std::string password, newPass, confirmPass;
	std::cin >> password;
	if (password == " ") return;

	std::string check_username, check_password;
	fin >> check_username;
	fin >> check_password;
	bool condition = false;
	fin.close();
																			//Remember to close text file
	while (condition == false)
	{
		if (check_username == username && check_password == password)
		{
			std::cout << "\n"; gotox(mid - 53 / 2);
			std::cout << "Enter the new password: ";
			std::cin >> newPass;
			if (newPass == " ")	return;

			std::cout << "\n"; gotox(mid - 53 / 2);
			std::cout << "Confirm your password: ";
			std::cin >> confirmPass;
			if (confirmPass == " ") return;

			if (newPass == confirmPass)
			{
				if (username[0] >= 'a' && username[0] <= 'z')
					fout.open("../StaffAccount/" + username + ".txt", std::ios::trunc);
				else if (username[0] >= '0' && username[0] <= '9')
					fout.open("../StudentAccount/" + username + ".txt", std::ios::trunc);
				fout << username << std::endl;
				fout << newPass;
				condition = true;
				fout.close();																//Remember to close text file

				//Display
				std::cout << "\n"; gotox(mid - 30 / 2);
				std::cout << "Change password successfully!\n";
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
			if (password == " ")
				return;
		}
	}
	std::cout << std::endl;
	std::cout << "Process done! The system will go back to the menu.";
	system("pause");
}
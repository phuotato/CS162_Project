#include "ChangePassword.h"
void changePassword(ifstream& fin, ofstream& fout)
{
	cout << "Enter the username: ";
	string username;
	cin >> username;
	if (username[0] >= 'a' && username[0] <= 'z')
		fin.open("../StaffAccount/" + username + ".txt", ios::in);
	else if (username[0] >= '0' && username[0] <= '9')
		fin.open("..StudentAccount/" + username + ".txt", ios::in);
	if (!fin)
	{
		cout << "Account Not Found! Please try again." << endl << endl;
		cout << "Process done! The system will go back to the menu." << endl;
		system("pause");
		return;
	}
	cout << "Input the password: ";
	string password, newPass, confirmPass;
	cin >> password;
	string check_username, check_password;
	fin >> check_username;
	fin >> check_password;
	bool condition = false;
	while (condition == false)
	{
		if (check_username == username && check_password == password)
		{
			cout << "Enter the new password: ";
			cin >> newPass;
			cout << "Confirm your password: ";
			cin >> confirmPass;
			if (newPass == confirmPass)
			{
				if (username[0] >= 'a' && username[0] <= 'z')
					fout.open("../StaffAccount/" + username + ".txt");
				else if (username[0] >= '0' && username[0] <= '9')
					fout.open("../StudentAccount/" + username + ".txt");
				fout << username << endl;
				fout << newPass;
				condition = true;
				cout << "Change password successfully!" << endl;
			}
			else
			{
				cout << "Wrong password. Please input again.";
			}
		}
		else
		{
			cout << "Wrong password. Please try again" << endl;
			cout << "Input the password: ";
			cin >> password;
		}
	}
	cout << endl;
	cout << "Process done! The system will go back to the menu.";
	system("pause");
}
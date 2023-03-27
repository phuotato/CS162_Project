#include "Universal.h"

//definition of constructor

void Date::GetDate(int& day, int& month, int& year) {
	const int month_31_days[7] = { 1, 3, 5, 7, 8, 10, 12 };
	const int month_30_days[4] = { 4, 6, 9, 11 };
	bool full_check;
	std::cin >> year;
	if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) {					// Check whether full year or not
		full_check = true;
	}
	else full_check = false;

	for (month = 0; month <= 0 || month >= 13; std::cin >> month) {		// Check month
		std::cout << "You have entered wrong month. Try again!\n Your month: ";
	}

	// Checking the day

	for (int i = 0; i < 7; i++) {
		if (month == month_31_days[i]) {
			for (day = 0; day <= 0 || day >= 32; std::cin >> day) {
				std::cout << "You have entered wrong day. Try again!\n Your day: ";
			}
			return;
		}
		else if (i <= 3 && month == month_30_days[i]) {
			for (day = 0; day <= 0 || day >= 31; std::cin >> day) {
				std::cout << "You have entered wrong day. Try again!\n Your day: ";
			}
			return;
		}
	}

	if (full_check) {
		for (day = 0; day <= 0 || day >= 30; std::cin >> day) {
			std::cout << "You have entered wrong day. Try again!\n Your day: ";
		}
		return;
	}
	else {
		for (day = 0; day <= 0 || day >= 29; std::cin >> day) {
			std::cout << "You have entered wrong day. Try again!\n Your day: ";
		}
		return;
	}



}
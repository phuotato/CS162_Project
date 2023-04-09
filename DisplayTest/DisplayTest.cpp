#include <iostream>
#include <tabulate/table.hpp>
using namespace tabulate;

int main() {
    // Set console size and title
    system("mode con: cols=90 lines=30");
    SetConsoleTitle(TEXT("FIT.HCMUS Management Program"));

    // welcome message
    tabulate::Table welcome_page;
    welcome_page.add_row({ "FIT.HCMUS Management System." }).format()
        .font_align(tabulate::FontAlign::center)
        .font_style({ tabulate::FontStyle::bold });
    std::cout << welcome_page << std::endl;

    // wait for user input to continue
    std::cout << "\n\n\n\nPress any key to continue...";
    std::cin.get();

    // clear screen and display menu
    system("cls");
    tabulate::Table menu;
    menu.add_row({ "Login as" })
        .add_row({ "1. Staff" })
        .add_row({ "2. Student" })
        .add_row({ "0. Exit" });
    menu.format().font_align(tabulate::FontAlign::center);
    std::cout << "\n\n\n\n" << menu << std::endl;

    // Get user input
    std::cout << "Your choice: ";
    int option;
    std::cin >> option;
    switch (option) {
    case 1:
        std::cout << "Staff";
        //Staff();
        break;
    case 2:
        std::cout << "Student";
        //login("../StudentAccount/");
        break;
    case 0:
        exit(0);
        break;
    default:
        std::cout << "Invalid input." << std::endl;
    }

    return 0;
}

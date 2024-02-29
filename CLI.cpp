#include <iostream>
#include <chrono>
#include <thread>
#include <string>

class CLI {
public:
    bool login_service_selected = false;
    std::string selected_login_service;
    bool user_logged_in = false;
    bool user_is_admin;

    int login() {
        int selected_login_number;
        while (!login_service_selected) {
            std::cout << "Please select a service to login with: \n"
                "[1] Google\n"
                "[2] Apple\n"
                "[3] Facebook\n";
            std::cin >> selected_login_number;
            if (selected_login_number < 1 || selected_login_number > 3) {
                std::cout << "Error: incorrect number selected, please enter a number between 1-3.\n\n";
            } else {
                login_service_selected = true;
            }
        }
        switch(selected_login_number) {
            case 1:
                selected_login_service = "Google";
                break;
            case 2:
                selected_login_service = "Apple";
                break;
            case 3:
                selected_login_service = "Facebook";
                break;
        }
        std::cout << "Taking you to " << selected_login_service << " to login...\n\n";
        
        std::string admin_user_selection;
        while(!user_logged_in) {
            std::cout << "(Login simulated for demonstration purposes, enter [ADMIN] for advanced user, or [BASIC] for basic features.)\n";
            std::cin >> admin_user_selection;
            if (admin_user_selection == "ADMIN") {
                user_is_admin = true;
                user_logged_in = true;
                std::cout << "\nWelcome back, admin_user!";
            } else if (admin_user_selection == "BASIC") {
                user_is_admin = false;
                user_logged_in = true;
                std::cout << "\nWelcome back, basic_user!";
            } else {
                std::cout << "Error: invalid command entered, please type either 'ADMIN' or 'BASIC'.\n\n";
            }
        };

        return 0;
    }
};

int main() {  
    std::cout << "\nWelcome to the Floorbot CLI!\n";

    CLI cli;
    cli.login();

    return 0;
}

#include <iostream>
#include <chrono>
#include <thread>
#include <string>

int main(int argc, char** argv) {  
    // Login/Authentication
    int selected_login_number;
    std::cout << "Welcome to the Floorbot CLI!\n";
    std::cout << "Please select a service to login with: \n"
        "[1] Google\n"
        "[2] Apple\n"
        "[3] Facebook\n";
    std::cin >> selected_login_number;
    std::string selected_login_service;
    switch(selected_login_number) {
        case 1:
            selected_login_service = "Google";
        case 2:
            selected_login_service = "Apple";
        case 3:
            selected_login_service = "Facebook";
    }
    std::cout << "Taking you to " << selected_login_service << "...";

    bool user_logged_in = false;
    bool user_is_admin;
    std::string admin_user_selection;
    while(!user_logged_in) {
        std::cout << "Login simulated for demonstration purposes, enter [ADMIN] for advanced user, or [BASIC] for basic features:\n";
        std::cin >> admin_user_selection;
        if (admin_user_selection == "ADMIN") {
            user_is_admin = true;
            user_logged_in = true;
            std::cout << "Welcome back, admin_user!";
        } else if (admin_user_selection == "BASIC") {
            user_is_admin = false;
            user_logged_in = true;
            std::cout << "Welcome back, basic_user!";
        } else {
            std::cout << "Error: invalid command entered, please type either 'ADMIN' or 'BASIC'.\n";
        }
    };


    return 0;
}

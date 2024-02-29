#include <iostream>
#include <chrono>
#include <thread>
#include <string>

#include "Floorbot.hpp"
#include "Account.hpp"
#include "Move.hpp"
#include "Diagnostics.hpp"
#include "Control.hpp"
#include "Scripts.hpp"
#include "Plugins.hpp"
#include "DummyObjects.hpp"

class CLI {
public:
    DummyObjects dummy_objects;
    bool user_logged_in = false;
    Account* current_user = nullptr;
    bool floorbot_selected = false;
    Floorbot* current_floorbot = nullptr;

    int login() {
        bool login_service_selected = false;
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
        std::string selected_login_service;
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
            std::cout << "(Login simulated for demonstration purposes, enter 'ADMIN' for advanced/technical user, or 'BASIC' for only basic features.)\n";
            std::cin >> admin_user_selection;
            if (admin_user_selection == "ADMIN") {
                current_user = &dummy_objects.admin_account;
                user_logged_in = true;
            } else if (admin_user_selection == "BASIC") {
                current_user = &dummy_objects.basic_account;
                user_logged_in = true;
            } else {
                std::cout << "Error: invalid command entered, please type either 'ADMIN' or 'BASIC'.\n\n";
            }
        };
        std::cout << "\nWelcome back, " << current_user->username << "!";
        return 0;
    }

    int select_robot() {
        int selected_floorbot_number;
        while (!floorbot_selected) {
            std::cout << "Please select a floorbot linked to your account to begin controlling: \n";
            int i = 1;
            for (Floorbot linked_floorbot : current_user->linked_floorbots) {
                std::cout << "[" << std::to_string(i) << "] " << linked_floorbot.name << std::endl;
            }
            std::cin >> selected_floorbot_number;
            if (selected_floorbot_number < 1 || selected_floorbot_number > current_user->linked_floorbots.size()) {
                std::cout << "Error: incorrect number selected, please enter a number between 1-3.\n\n";
            } else {
                floorbot_selected = true;
            }
        }
    }
};

int main() {  
    std::cout << "\nWelcome to the Floorbot CLI!\n";

    CLI cli;
    cli.login();
    


    return 0;
}

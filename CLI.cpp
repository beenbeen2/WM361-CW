#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>

#include "DummyObjects.hpp"
#include "Floorbot.hpp"
#include "Account.hpp"
#include "Move.hpp"
#include "Diagnostics.hpp"
#include "Control.hpp"
#include "Scripts.hpp"
#include "CommandHandler.hpp"

class CLI {
public:
    DummyObjects dummy_objects;
    CommandHandler command_handler;
    bool user_logged_in = false;
    Account current_user;
    bool floorbot_selected = false;
    Floorbot current_floorbot;

    std::unordered_map<std::string, std::string> login_service_map = {
        {"1", "Google"},
        {"2", "Apple"},
        {"3", "Facebook"},
    };
    std::unordered_map<std::string, Account> account_map = {
        {"BASIC", dummy_objects.basic_account},
        {"ADMIN", dummy_objects.admin_account},
    };

    std::vector<std::string> split_string(std::string input) {
        std::vector<std::string> input_list;
        std::istringstream command_stream(input);

        std::string command;
        while (std::getline(command_stream, command, ' ')) {
            input_list.push_back(command);
        }

        return input_list;
    };

    int login() {
        bool login_service_selected = false;
        std::string login_service;
        while (!login_service_selected) {
            std::cout << "Please select a service to login with:" << std::endl
                << "[1] Google" << std::endl
                << "[2] Apple" << std::endl
                << "[3] Facebook" << std::endl;
            std::cin >> login_service;

            if (!login_service_map.count(login_service)) {
                std::cout << "Error: incorrect number selected, please enter a number between 1-3.\n\n";
                continue;
            }

            login_service = login_service_map[login_service];
            login_service_selected = true;
        }

        std::cout << "Taking you to " << login_service << " to login...\n\n";

// Dummy login proccess for demonstration.
        std::string account_selection;
        while(!user_logged_in) {
            std::cout << "(Login simulated for demonstration purposes, enter 'ADMIN' for advanced/technical user, or 'BASIC' for only basic features.)" << std::endl;
            std::cin >> account_selection;

            if (!account_map.count(account_selection)) {
                std::cout << "Error: invalid command entered, please type either 'ADMIN' or 'BASIC'.\n\n";
                continue;
            }

            current_user = account_map[account_selection];
            user_logged_in = true;
        }
        std::cout << "Welcome back, " << current_user.username << "!" << std::endl;
        return 0;
    };

    int select_robot() {
        int selected_floorbot_number;
        while (!floorbot_selected) {
            std::cout << std::endl << "Please select a floorbot linked to your account to begin controlling:" << std::endl;
            int i = 1;
            for (Floorbot linked_floorbot : current_user.linked_floorbots) {
                std::cout << "[" << std::to_string(i) << "] " << linked_floorbot.get_name() << std::endl;
                i++;
            }
            std::cin >> selected_floorbot_number;
            if (selected_floorbot_number < 1 || selected_floorbot_number > current_user.linked_floorbots.size()) {
                std::cout << "Error: incorrect number selected, please enter a number between 1-3.\n\n";
            } else {
                current_floorbot = current_user.linked_floorbots[selected_floorbot_number];
                floorbot_selected = true;
            }
        }
        std::cout << std::endl << "You have selected " << current_floorbot.get_name() << "to control." << std::endl;
        return 0;
    };

    int input_command(std::string input) {
        std::string command_input;
        std::string flag_input;
        std::string arg_input;

        std::cout << "Please enter a command or type '--help' to see a list of available commands." << std::endl;
        std::cin >> input;

        std::vector<std::string> input_list = split_string(input);

        if (input_list.size() == 0) {
            std::cout << "Error: please enter a command.";
            return 1;
        };
        if (input_list.size() > 0) { command_input = input_list[0]; };
        if (input_list.size() > 1) { flag_input = input_list[1]; };
        if (input_list.size() > 2) { arg_input = input_list[2]; };
        if (input_list.size() >= 4) {
            std::cout << "Error: too many parameters enter, at most a command, flag, and argument should be entered.";
            return 1;
        };

        command_handler.parse_command(
            command_input,
            flag_input,
            arg_input,
            current_floorbot
        );

        return 0;
    }
};

int main() {  
    CLI cli;
    
    std::cout << std::endl << "Welcome to the Floorbot CLI!" << std::endl;

    cli.login();
    if (!cli.user_logged_in) {
        std::cout << "Error: CLI has not logged in correctly, exiting.";
        return 1;
    }

    cli.select_robot();
    if (!cli.floorbot_selected) {
        std::cout << "Error: CLI has not selected a floorbot correctly, exiting.";
        return 1;
    }
    
    return 0;
}

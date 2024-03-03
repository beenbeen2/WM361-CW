#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "./components/Plugin.hpp"
#include "./components/Script.hpp"
#include "./components/Floorbot.hpp"
#include "./components/Account.hpp"

#include "CLICache.cpp"
#include "Database.hpp"
#include "Utils.hpp"

#include "handlers/MoveHandler.hpp"
#include "handlers/DiagnosticsHandler.hpp"
#include "handlers/ScriptsHandler.hpp"
#include "handlers/PluginsHandler.hpp"
#include "handlers/ControlHandler.hpp"

class CLI: virtual public CLICache {
private:
    Database database;
    Utils utils;
    MoveHandler move;
    DiagnosticsHandler diagnostics;
    ScriptsHandler scripts;
    PluginsHandler plugins;
    ControlHandler control;

public:
    enum class Command { move, diagnostics, plugins, scripts, control, help, exit };
    std::unordered_map<std::string, Command> command_map = {
        {"move", Command::move},
        {"diagnostics", Command::diagnostics},
        {"plugins", Command::plugins},
        {"scripts", Command::scripts},
        {"control", Command::control},
        {"--help", Command::help},
        {"EXIT", Command::exit},
    };

    std::unordered_map<std::string, std::string> login_service_map = {
        {"1", "Google"},
        {"2", "Apple"},
        {"3", "Facebook"},
    };
    std::unordered_map<std::string, std::shared_ptr<Account>> account_map = {
        {"1", std::make_shared<Account>(database.basic_account)},
        {"2", std::make_shared<Account>(database.admin_account)},
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
            std::cout << "(Login simulated for demonstration purposes, "
                << "do you want to act as an admin/advanced user or a basic user:)" << std::endl
                << "[1] Basic User" << std::endl
                << "[2] Admin/Advanced User" << std::endl;
            std::cin >> account_selection;

            if (!account_map.count(account_selection)) {
                std::cout << "Error: incorrect number selected, please enter a number between 1-2.\n\n";
                continue;
            }

            current_user = account_map[account_selection];
            user_logged_in = true;
        }
        std::cout << "Welcome back, " << current_user->username << "!" << std::endl;
        return 0;
    };

    int select_robot() {
        int selected_floorbot_number;
        while (!floorbot_selected) {
            std::cout << std::endl << "Please select a floorbot linked to your account to begin controlling:" << std::endl;
            int i = 1;
            for (std::shared_ptr<Floorbot> linked_floorbot : current_user->linked_floorbots) {
                std::cout << "[" << std::to_string(i) << "] " << linked_floorbot->get_name() << std::endl;
                i++;
            }
            std::cin >> selected_floorbot_number;
            if (selected_floorbot_number < 1 || selected_floorbot_number > current_user->linked_floorbots.size()) {
                std::cout << "Error: incorrect number selected, please enter a number between 1-3.\n\n";
            } else {
                current_floorbot = current_user->linked_floorbots[selected_floorbot_number-1];
                floorbot_selected = true;
            }
        }
        std::cout << "You have selected " << current_floorbot->get_name() << " to control." << std::endl;
        return 0;
    };

    int parse_command(std::string input) {
        std::string command_input;
        std::string flag_input;
        std::string arg_input;

        if (input.empty()) {
            std::cout << "Error: please enter a command.";
        };

        std::vector<std::string> input_list = utils.split_command(input);
        if (input_list.size() > 0) { command_input = input_list[0]; };
        if (input_list.size() > 1) { flag_input = input_list[1]; };
        if (input_list.size() > 2) { arg_input = input_list[2]; };
        if (input_list.size() >= 4) {
            std::cout << "Error: too many parameters enter, at most a command, flag, and argument should be entered.";
            return 1;
        };
        if (!command_map.count(command_input)) {
            std::cout << "Error: invalid command entered.";
            return 1;
        }
        Command command = command_map[command_input];

        std::cout << std::endl;
        switch(command) {
            case Command::move: 
                move.parse_command(flag_input, arg_input);
                break;
            case Command::diagnostics:
                diagnostics.parse_command(flag_input, arg_input);
                break;
            case Command::plugins:
                plugins.parse_command(flag_input, arg_input);
                break;
            case Command::scripts:
                scripts.parse_command(flag_input, arg_input);
                break;
            case Command::control:
                control.parse_command(flag_input, arg_input);
                break;
            case Command::help:
                break;
            case Command::exit:
                std::cout << "Exiting Floorbot CLI." << std::endl;
                exit(0);
        };

        return 0;
    };

    int enter_command() {
        std::string input = utils.get_input_command();
        parse_command(input);
        return 0;
    };

};

int main() {  
    CLI cli;
    
    std::cout << std::endl << "Welcome to the Floorbot Commander CLI!" << std::endl;

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

    std::cout << std::endl << "Please enter a command, "
        << "type '--help' to see a list of available commands, "
        << "or 'EXIT' to exit the CLI:" << std::endl;
    while(true) { cli.enter_command(); }
    return 0;
}

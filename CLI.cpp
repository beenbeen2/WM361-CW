#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "./components/Plugin.hpp"
#include "./components/Script.hpp"
#include "./components/Floorbot.hpp"
#include "./components/Account.hpp"

#include "services/CLICache.cpp"
#include "services/Database.hpp"
#include "services/Utils.hpp"
#include "services/Help.hpp"

#include "handlers/MoveHandler.hpp"
#include "handlers/DiagnosticsHandler.hpp"
#include "handlers/ScriptsHandler.hpp"
#include "handlers/PluginsHandler.hpp"
#include "handlers/ControlHandler.hpp"

class CLI: virtual public CLICache {
private:
    Database database;
    Utils utils;
    Help help;
    MoveHandler move;
    DiagnosticsHandler diagnostics;
    ScriptsHandler scripts;
    PluginsHandler plugins;
    ControlHandler control;

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

    int parse_command(std::string input) {
        std::string command_input;
        std::string flag_input;
        std::string arg_input;

        if (input.empty()) {
            std::cerr << "Error: please enter a command" << std::endl << std::endl;
        };

        std::vector<std::string> input_list = utils.split_command(input);
        if (input_list.size() > 0) { command_input = input_list[0]; };
        if (input_list.size() > 1) { flag_input = input_list[1]; };
        if (input_list.size() > 2) { arg_input = input_list[2]; };
        if (input_list.size() >= 4) {
            std::cerr << "Error: too many parameters enter, at most a command, flag, and argument should be entered" << std::endl << std::endl;
            return 1;
        };
        if (!command_map.count(command_input)) {
            std::cerr << "Error: invalid command entered." << std::endl << std::endl;
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
                if (!current_user->is_admin) {
                    std::cerr << "Error: Scripts may damage your floorbot and are restricted to admin users only." 
                    << std::endl << std::endl;
                    return 0;
                }
                scripts.parse_command(flag_input, arg_input);
                break;
            case Command::control:
                control.parse_command(flag_input, arg_input);
                break;
            case Command::help:
                help.general();
                help.move();
                help.diagnostics();
                help.plugins();
                if (current_user->is_admin) {
                    help.scripts();
                }
                help.control();
                break;
            case Command::exit:
                std::cout << "Exiting Floorbot CLI." << std::endl << std::endl;
                exit(0);
        };

        return 0;
    };

    int welcome() {
        std::cout << "Welcome back to the...";
        std::cout << R"(     
  ___  _                 ___       _         ___                                    _                 ___  _     ___ 
 | __|| | ___  ___  _ _ | _ ) ___ | |_      / __| ___  _ __   _ __   __ _  _ _   __| | ___  _ _      / __|| |   |_ _|
 | _| | |/ _ \/ _ \| '_|| _ \/ _ \|  _|    | (__ / _ \| '  \ | '  \ / _` || ' \ / _` |/ -_)| '_|    | (__ | |__  | | 
 |_|  |_|\___/\___/|_|  |___/\___/ \__|     \___|\___/|_|_|_||_|_|_|\__,_||_||_|\__,_|\___||_|       \___||____||___|                                                                                                       
        )" << std::endl;
        return 1;                                                                                                                                             
    }

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
                std::cerr << "Error: incorrect number selected, please enter a number between 1-3.\n\n";
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
                std::cerr << "Error: incorrect number selected, please enter a number between 1-2.\n\n" << std::endl << std::endl;
                continue;
            }

            current_user = account_map[account_selection];
            user_logged_in = true;
        }
        std::cout << std::endl << "Welcome back, " << current_user->username << "!" << std::endl;
        return 0;
    };

    int select_robot() {
        int num_floorbots = 0;
        std::string selected_floorbot_str;
        int selected_floorbot_number;
        while (!floorbot_selected) {
            std::cout << std::endl << "Please select a floorbot linked to your account to begin controlling:" << std::endl;
            int i = 1;
            for (std::shared_ptr<Floorbot> linked_floorbot : current_user->linked_floorbots) {
                std::cout << "[" << std::to_string(i) << "] " << linked_floorbot->get_name() << std::endl;
                i++;
            }
            std::cin >> selected_floorbot_str;
            num_floorbots = current_user->linked_floorbots.size();
            try {
                selected_floorbot_number = std::stoi(selected_floorbot_str);
            } catch (std::invalid_argument& error) {
                std::cerr << "Error: the please enter a number." << std::endl << std::endl;
                return 1;
            }
            if (selected_floorbot_number < 1 || selected_floorbot_number > num_floorbots) {
                std::cerr << "Error: incorrect number selected, please enter a number between 1-" << num_floorbots << "." << std::endl;
            } else {
                current_floorbot = current_user->linked_floorbots[selected_floorbot_number-1];
                floorbot_selected = true;
            }
        }
        std::cout << std::endl << "You have selected " << current_floorbot->get_name() << " to control." << std::endl << std::endl;
        return 0;
    };

    int enter_command() {
        std::string input = utils.get_input_command();
        parse_command(input);
        return 0;
    };

public:
    int run() {
        welcome();
        login();
        select_robot();
        std::cout << std::endl << "Please enter a command, type '--help' to see a list of available commands, or 'EXIT' to exit the CLI:" << std::endl;
        while(true) { enter_command(); }
        return 0;
    }
};

int main() {  
    CLI cli;
    cli.run();
    return 0;
}

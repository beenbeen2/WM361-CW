#ifndef COMMANDPARSER
#define COMMANDPARSER

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>

class CommandParser {
public:    
    enum class Command { move, diagnostics, plugins, scripts, robot };
    // enum class ScriptFlag { list_installed, list_available, install, uninstall };
    // enum class ScriptFlag { list_installed, list_available, install, uninstall, enable, disable };

    std::unordered_map<std::string, Command> command_map = {
        {"move", Command::move},
        {"diagnostics", Command::diagnostics},
        {"plugins", Command::plugins},
        {"scripts", Command::scripts},
        {"robot", Command::robot},
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

    int parse_input(std::string input) {
        std::vector<std::string> input_list = split_string(input);

        if (input_list.empty()) {
            std::cout << "Error: please enter a command.";
            // display help?
            return 1;
        };
        std::string command_input = input_list[0];
        
        if (!command_map.count(command_input)) {
            std::cout << "Error: invalid command entered.";
            // display help?
            return 1;
        }
        Command command = command_map[command_input];

        switch(command) {
            case Command::move: 
                std::cout << "moving!";
                // move();
                break;
            case Command::diagnostics:
                std::cout << "diagnosing!";
                // diagnostics();
                break;
            case Command::plugins:
                std::cout << "plugining!";
                // plugins();
                break;
            case Command::scripts:
                std::cout << "scripting!";
                // scripts();
                break;
            case Command::robot:
                std::cout << "roboting!";
                // robot();
                break;
        }

        return 0;
    }
};

int main () {
    CommandParser parser;
    std::string input;

    std::cout << "Enter a command:\n";
    getline(std::cin, input);
    // std::cout << input;
    parser.parse_input(input);

    return 0;
};

#endif
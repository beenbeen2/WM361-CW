#ifndef UTILS
#define UTILS

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

class Utils {
public:
    std::vector<std::string> string_to_vector(std::string input) {
        std::vector<std::string> input_list;
        std::istringstream command_stream(input);

        std::string command;
        while (std::getline(command_stream, command, ' ')) {
            input_list.push_back(command);
        }

        return input_list;
    };

    bool get_confirmation(bool default_to_true = false) {
        std::unordered_map<std::string, bool> bool_map = {
            {"0", false},
            {"false", false},
            {"False", false},
            {"NO", false},
            {"No", false},
            {"no", false},
            {"N", false},
            {"n", false},
            {"1", true},
            {"true", true},
            {"True", true},
            {"YES", true},
            {"Yes", true},
            {"yes", true},
            {"Y", true},
            {"y", true}
        };

        if (default_to_true) {
            std::cout << "[Y/n]" << std::endl;
        } else {
            std::cout << "[y/N]" << std::endl;
        }
        
        std::string input;
        bool valid_confirmation_entered = false;
        while (!valid_confirmation_entered) {
            std::getline(std::cin, input);
            if (!input.empty() && !bool_map.count(input)) {
                std::cout << "Error: invalid yes/no entered, "
                << "valid options look like '0', 'yes', 'true' etc." << std::endl;
            } else {
                valid_confirmation_entered = true;
            }
        };

        if (input.empty()) { return default_to_true; }
        bool bool_input = bool_map[input];
        return bool_input;
    };

    std::string get_input_command() {
        std::string command_str;
        std::string subcommand_str;
        std::cin >> command_str;
        std::getline(std::cin, subcommand_str);
        std::stringstream linestream(subcommand_str);
        // Workaround for issues with getline() not halting programme for user input.
        std::string input = command_str + linestream.str();
        return input;
    };
};

#endif
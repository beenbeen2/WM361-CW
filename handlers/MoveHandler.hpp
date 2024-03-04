#ifndef MOVEHANDLER
#define MOVEHANDLER

#include "../CLICache.hpp"
#include "../Database.hpp"
#include "../Utils.hpp"

class MoveHandler: virtual private CLICache {
private:
    Database database;
    Utils utils;

public:
    enum class Flag { forward, back, right, left, help };
    std::unordered_map<std::string, Flag> flag_map = {
        {"--f", Flag::forward},
        {"--forward", Flag::forward},
        {"--b", Flag::back},
        {"--back", Flag::back},
        {"--r", Flag::right},
        {"--right", Flag::right},
        {"--l", Flag::left},
        {"--left", Flag::left},
        {"--help", Flag::help},
    };

    int parse_command(std::string flag_input, std::string arg_input) {
        int distance;
        Flag flag = flag_map[flag_input];
        if (flag != Flag::help) {
            if (!flag_map.count(flag_input)) {
                std::cout << "Error: invalid direction flag entered." << std::endl << std::endl;
                return 1;
            }

            if (arg_input.empty()) {
                std::cout << "Error: please enter a distance value." << std::endl << std::endl;
                return 1;
            }

            try {
                distance = std::stoi(arg_input);
            } catch (std::invalid_argument& error) {
                std::cout << "Error: the distance must be an integer." << std::endl << std::endl;
                return 1;
            }
        }

        switch(flag) {
            case Flag::forward:
                current_floorbot->move_forward(distance);
                break;
            case Flag::back:
                current_floorbot->move_back(distance);
                break;
            case Flag::left:
                current_floorbot->move_left(distance);
                break;
            case Flag::right:
                current_floorbot->move_right(distance);
                break;
            case Flag::help:
                help();
                break;
        }

        std::cout << "Floorbot has moved " << distance << "cm to (" 
            << current_floorbot->get_x_coord() << ", " << current_floorbot->get_y_coord() << ")." << std::endl << std::endl;
        return 0;
    }

    void help() {
        std::cout << std::endl << "Available commands:" << std::endl;
        std::cout << "move " << std::endl;
        std::cout << "    --f/--forward <distance>" << std::endl
                  << "    --b/--back <distance>" << std::endl
                  << "    --r/--right <distance>" << std::endl
                  << "    --l/--left <distance>" << std::endl
                  << "    --help (display this message)" << std::endl << std::endl;
    }
};

#endif
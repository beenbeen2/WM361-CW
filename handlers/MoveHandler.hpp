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
    enum class Flag { forward, back, right, left };
    std::unordered_map<std::string, Flag> flag_map = {
        {"--forward", Flag::forward},
        {"--back", Flag::back},
        {"--right", Flag::right},
        {"--left", Flag::left},
    };

    int parse_command(std::string flag_input, std::string arg_input) {
        if (!flag_map.count(flag_input)) {
            std::cout << "Error: invalid direction flag entered." << std::endl << std::endl;
            return 1;
        }
        Flag direction = flag_map[flag_input];

        if (arg_input.empty()) {
            std::cout << "Error: please enter a distance value." << std::endl << std::endl;
            return 1;
        }

        int distance;
        try {
            distance = std::stoi(arg_input);
        } catch (std::invalid_argument& error) {
            std::cout << "Error: the distance must be an integer." << std::endl << std::endl;
            return 1;
        }

        switch(direction) {
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
        }

        std::cout << "Floorbot has moved " << distance << "cm to (" 
            << current_floorbot->get_x_coord() << ", " << current_floorbot->get_y_coord() << ")." << std::endl << std::endl;
        return 0;
    }
};

#endif
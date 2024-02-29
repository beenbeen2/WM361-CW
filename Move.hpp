#ifndef MOVE
#define MOVE

#include <iostream>
#include <string>
#include <unordered_map>

class Move {
public:
    enum class Flag { forward, back, right, left };
    std::unordered_map<std::string, Flag> move_flag_map = {
        {"--forward", Flag::forward},
        {"--backward", Flag::back},
        {"--right", Flag::right},
        {"--left", Flag::left},
    };

    int parse_command(Floorbot floorbot, std::string flag_input, std::string arg_input) {
        if (arg_input.empty()) {
            std::cout << "Error: please enter a distance value.";
            return 1;
        }
        if (!move_flag_map.count(flag_input)) {
            std::cout << "Error: invalid direction flag entered.";
            return 1;
        }
        Floorbot::MoveFlag direction = move_flag_map[flag_input];

        int distance;
        try {
            distance = std::stoi(arg_input);
        } catch (const std::invalid_argument& e) {
            std::cout << "Error: the distance must be an integer.";
            return 1;
        }

        switch(direction) {
            case MoveFlag::forward:
                floorbot.move_forward(distance);
                break;
            case MoveFlag::back:
                floorbot.move_back(distance);
                break;
            case MoveFlag::left:
                floorbot.move_left(distance);
                break;
            case MoveFlag::right:
                floorbot.move_right(distance);
                break;
        }

        std::cout << "Floorbot has moved " << distance << "cm to (" 
            << floorbot.get_x_coord() << ", " << floorbot.get_y_coord() << ")." << std::endl;
        return 0;
    }
};

#endif
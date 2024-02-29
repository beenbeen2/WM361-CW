#include <iostream>
#include <string>
#include <unordered_map>

// GET FROM FLOORBOT
enum class MoveDirection { forward, back, right, left };

class Move {
public:
    std::unordered_map<std::string, MoveDirection> direction_flag_map = {
        {"--forward", MoveDirection::forward},
        {"--backward", MoveDirection::back},
        {"--right", MoveDirection::right},
        {"--left", MoveDirection::left},
    };

    int parse_input(std::string flag_input, int distance) {
        MoveDirection direction = direction_flag_map[flag_input];
        move(direction, distance);
    }
};
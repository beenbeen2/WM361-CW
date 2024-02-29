#include <iostream>
#include <string>
#include <unordered_map>

class Move {
public:
    enum class DiagnosticsFlag { print, save, submit };
    std::unordered_map<std::string, DiagnosticsFlag> diagnostic_flag_map = {
        {"--print", DiagnosticsFlag::print},
        {"--save", DiagnosticsFlag::save},
        {"--submit", DiagnosticsFlag::submit},
    };

    int parse_input() {

    }


};
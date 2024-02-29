#ifndef DIAGNOSTICS
#define DIAGNOSTICS

#include <iostream>
#include <string>
#include <unordered_map>

class Diagnostics {
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

int main() {
    std::cout << "\n\n\n\nStarting!\n\n";

    // std::cout << "Robot name is '" << Robot.name << "'\n";
    // std::cout << "Robot model is '" << Robot.model << "'\n";
    // std::cout << "Robot is on version " << Robot.get_version() << "\n";
    // std::cout << "Robot chipset is '" << Robot.chipset << "'\n";
    // std::cout << "Robot bin capacity is " << Robot.get_bin_capacity() << "%\n";
    // std::cout << "Robot battery level is " << Robot.get_battery_level() << "%\n";
    // std::cout << "Robot battery health is " << Robot.get_battery_health() << "%\n";
    // std::cout << "Robot filter health is " << Robot.get_filter_health() << "%\n";
    // std::cout << "Robot power usage is " << Robot.get_power_usage() << "W\n";

    // std::this_thread::sleep_for(std::chrono::milliseconds(1));
    // std::chrono::system_clock::duration runtime = Robot.get_runtime();
    // std::cout << "Robot has been running for " << runtime.count() << "ns";

    // std::cout << "\n\nDone! \n\n\n";
    return 1;
};

#endif
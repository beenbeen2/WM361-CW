#ifndef CONTROLHANDLER
#define CONTROLHANDLER

#include "../services/CLICache.hpp"
#include "../services/Database.hpp"
#include "../services/Utils.hpp"

class ControlHandler: virtual private CLICache {
private:
    Database database;
    Utils utils;
    Help help;

public:
    enum class Flag { restart, power_off, power_on, factory_reset, help };
    std::unordered_map<std::string, Flag> flag_map = {
        {"--restart", Flag::restart},
        {"--power_off", Flag::power_off},
        {"--power_on", Flag::power_on},
        {"--factory_reset", Flag::factory_reset},
        {"--help", Flag::help},
    };

    int parse_command(std::string flag_input, std::string arg_input = "") {
        if (!flag_map.count(flag_input)) {
            std::cout << "Error: invalid flag entered." << std::endl << std::endl;
            return 1;
        }
        Flag flag = flag_map[flag_input];
        
        switch(flag) {
            case Flag::restart:
                restart();
                break;
            case Flag::power_off:
                power_off();
                break;
            case Flag::power_on:
                power_on();
                break;
            case Flag::factory_reset:
                factory_reset();
                break;
            case Flag::help:
                help.control();
                break;
        }
        return 0;
    };

    int restart() {
        std::cout << "Restarting " << current_floorbot->get_name() << "...";
        current_floorbot->restart();
        std::cout << current_floorbot->get_name() << " restarted successfully." << std::endl << std::endl;
        return 0;
    };

    int power_off() {
        if (!current_floorbot->get_powered_on()) {
            std::cout << "Error: " << current_floorbot->get_name() << " is already off!" << std::endl << std::endl;
            return 1;
        }
        std::cout << "Turning " << current_floorbot->get_name() << " off..." << std::endl;
        current_floorbot->power_off();
        // select another robot?
        std::cout << current_floorbot->get_name() << " powered off." << std::endl << std::endl;
        return 0;
    };

    int power_on() {
        if (current_floorbot->get_powered_on()) {
            std::cout << "Error: " << current_floorbot->get_name() << " is already on!" << std::endl << std::endl;
            return 1;
        }
        std::cout << "Turning " << current_floorbot->get_name() << " on..." << std::endl;
        current_floorbot->power_on();
        std::cout << current_floorbot->get_name() << " powered on." << std::endl << std::endl;
        return 0;
    };

    int factory_reset() {
        std::cout 
            << "This will erase all installed updates and plugins from the floorbot, "
            << "are you sure you want to continue? ";
        if (utils.get_confirmation(false)) {
            std::cout << "Factory resetting " << current_floorbot->get_name() << "..." << std::endl;
            current_floorbot->factory_reset();
            // select another robot?
            std::cout << current_floorbot->get_name() << " reset to factory conditions." << std::endl << std::endl;
        } else {
            std::cout << "Factory reset cancelled." << std::endl << std::endl;
        };
        return 0;
    };
};

#endif
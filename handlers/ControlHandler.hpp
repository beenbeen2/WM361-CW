#ifndef CONTROLHANDLER
#define CONTROLHANDLER

#include "../CLICache.hpp"
#include "../Database.hpp"
#include "../Utils.hpp"

class ControlHandler: virtual CLICache {
public:
    Database database;
    Utils utils;

    enum class Flag { restart, power_off, power_on, factory_reset };
    std::unordered_map<std::string, Flag> flag_map = {
        {"--restart", Flag::restart},
        {"--power_off", Flag::power_off},
        {"--power_off", Flag::power_on},
        {"--factory_reset", Flag::factory_reset},
    };

    int parse_command(Floorbot floorbot, std::string flag_input, std::string arg_input = "") {
        if (!flag_map.count(flag_input)) {
            std::cout << "Error: invalid flag entered.";
            return 1;
        }
        Flag flag = flag_map[flag_input];
        
        switch(flag) {
            case Flag::restart:
                restart(floorbot);
                break;
            case Flag::power_off:
                power_off(floorbot);
                break;
            case Flag::power_on:
                power_on(floorbot);
                break;
            case Flag::factory_reset:
                factory_reset(floorbot);
                break;
        }
        return 0;
    };

    int restart(Floorbot floorbot) {
        std::cout << "Restarting " << floorbot.get_name() << "...";
        floorbot.restart();
        return 0;
    };

    int power_off(Floorbot floorbot) {
        std::cout << "Turning " << floorbot.get_name() << " off...";
        floorbot.power_off();
        // select another robot?
        std::cout << floorbot.get_name() << " powered off." << std::endl;
        return 0;
    };

    int power_on(Floorbot floorbot) {
        std::cout << "Turning " << floorbot.get_name() << " on..." << std::endl;
        floorbot.power_on();
        std::cout << floorbot.get_name() << " powered on." << std::endl;
        return 0;
    };

    int factory_reset(Floorbot floorbot) {
        std::cout 
            << "This will erase all installed updates and plugins from the floorbot, "
            << "are you sure you want to continue? ";
        if (get_confirmation(false)) {
            std::cout << "Factory resetting " << floorbot.get_name() << "..." << std::endl;
            floorbot.factory_reset();
            // select another robot?
            std::cout << floorbot.get_name() << " reset to factory conditions." << std::endl;
        } else {
            std::cout << "Factory reset cancelled." << std::endl;
        };
        return 0;
    };
};

#endif
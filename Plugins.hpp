#ifndef PLUGINS
#define PLUGINS

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Floorbot.hpp"
#include "DummyObjects.hpp"

class Plugins {
public:
    enum class Flag { list, install, uninstall, enable, disable };
    std::unordered_map<std::string, Flag> flag_map = {
        {"--list", Flag::list},
        {"--install", Flag::install},
        {"--uninstall", Flag::uninstall},
        {"--enable", Flag::enable},
        {"--disable", Flag::disable},
    };

    DummyObjects dummy_objects;
    std::vector<Plugin> available_plugins = {
        dummy_objects.eco_mode_plugin,
        dummy_objects.filter_warning_plugin
    };

    int parse_command(Floorbot floorbot, std::string flag_input, std::string arg_input = "") {
        if (!flag_map.count(flag_input)) {
            std::cout << "Error: invalid direction flag entered.";
            return 1;
        }
        Flag flag = flag_map[flag_input];

        switch(flag) {
            case Flag::list:

                list(floorbot, arg_input);
                break;
            case Flag::install:
                install(floorbot);
                break;
            case Flag::uninstall:
                uninstall(floorbot);
                break;
            case Flag::enable:
                enable(floorbot);
                break;
            case Flag::disable:
                disable(floorbot);
                break;
        }
        return 0;
        return 0;
    };

    int list(Floorbot floorbot, std::string filter) {
        if (filter == "installed") {
            
        }

        return 0;
    }

    int install(Floorbot floorbot) {
        
        return 0;
    }

    int uninstall(Floorbot floorbot) {
        
        return 0;
    }

    int enable(Floorbot floorbot) {
        
        return 0;
    }

    int disable(Floorbot floorbot) {
        
        return 0;
    }
};

#endif
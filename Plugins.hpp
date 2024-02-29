#ifndef PLUGINS
#define PLUGINS

class Plugins {
public:
    enum class Flag { list, install, uninstall, enable, disable };
    std::unordered_map<std::string, Flag> plugin_flag_map = {
        {"--list", Flag::list},
        {"--install", Flag::install},
        {"--uninstall", Flag::uninstall},
        {"--enable", Flag::enable},
        {"--disable", Flag::disable},
    };

    int parse_command(Floorbot floorbot, std::string flag_input, std::string arg_input = "") {
        return 0;
    };

    int list(std::string filter) {
        if (filter == "installed") {
            
        }

        return 0;
    }

    int install() {
        
        return 0;
    }

    int uninstall() {
        
        return 0;
    }

    int enable() {
        
        return 0;
    }

    int disable() {
        
        return 0;
    }
};

#endif
#ifndef SCRIPTSHANDLER
#define SCRIPTSHANDLER

#include "../CLICache.hpp"
#include "../Database.hpp"
#include "../Utils.hpp"
  
class ScriptsHandler: virtual CLICache {
public:
    Database database;
    Utils utils;
    
    enum class ScriptsFlag { list, install, uninstall, run };
    std::unordered_map<std::string, ScriptsFlag> scripts_flag_map = {
        {"--list", ScriptsFlag::list},
        {"--install", ScriptsFlag::install},
        {"--uninstall", ScriptsFlag::uninstall},
        {"--run", ScriptsFlag::run},
    };

    bool script_is_available(std::string scriptname) {
        for (Script script : available_scripts) {
            if (script.name == scriptname) { return true; }
        }
        return false;
    }
    bool script_is_installed(std::string scriptname) {
        for (Script script : installed_scripts) {
            if (script.name == scriptname) { return true; }
        }
        return false;
    }

    int parse_scripts_command(Floorbot floorbot, std::string flag_input, std::string arg_input) {
        if (!scripts_flag_map.count(flag_input)) {
            std::cout << "Error: invalid flag entered.";
            return 1;
        }
        ScriptsFlag flag = scripts_flag_map[flag_input];
        
        bool only_installed;
        std::string scriptname;
        if (flag == ScriptsFlag::list) {
            std::istringstream(arg_input) >> only_installed;
        } else {
            scriptname = arg_input;
        }
        switch(flag) {
            case ScriptsFlag::list:
                list(only_installed);
                break;
            case ScriptsFlag::install:
                install(scriptname);
                break;
            case ScriptsFlag::uninstall:
                uninstall(scriptname);
                break;
            case ScriptsFlag::run:
                run(scriptname);
                break;
        }
        return 0;
    }

    int list(bool only_installed) {
        int i = 1;
        if (only_installed) {
            for (Script script : installed_scripts) {
                std::cout << std::to_string(i) << ". " << script.name << std::endl;
                i++;
            }
        } else {
            for (Script script : available_scripts) {
                std::cout << std::to_string(i) << ". " << script.name << std::endl;
                i++;
            }
        }
        return 0;
    }
    
    int install(std::string scriptname) {
        if (!script_is_available(scriptname)) {
            std::cout << "Error: script could not be located, is the script name correct?" << std::endl;
            return 1;
        }
        if (script_is_installed(scriptname)) {
            std::cout << "Error: script is already installed!" << std::endl;
            return 1;
        }
        std::cout << "Installing " << scriptname << "..." << std::endl;

        return 0;
    }

    int uninstall(std::string scriptname) {
        std::cout << "Uninstalling " << scriptname << "..."  << std::endl;
        return 0;
    }

    int run(std::string scriptname) {
        std::cout << "Searching for " << scriptname << "..."  << std::endl;
        std::vector<std::string> command_set;
        bool script_found = false;
        for (Script script : available_scripts) {
            if (script.name == scriptname) {
                command_set = script.command_set;
                script_found = true;
                break;
            }
        }
        if (!script_found) {
            std::cout << "Error: no script exists with the name '"
            << scriptname << "'" << std::endl;
            return 1;
        }

        std::cout << scriptname << " found, starting:" << std::endl;
        for (std::string command : command_set) {
            
        };
        return 0;
    }
};

#endif
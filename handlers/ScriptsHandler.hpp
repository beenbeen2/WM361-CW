#ifndef SCRIPTSHANDLER
#define SCRIPTSHANDLER

#include "../CLICache.hpp"
#include "../Database.hpp"
#include "../Utils.hpp"
  
class ScriptsHandler: virtual private CLICache {
private:
    Database database;
    Utils utils;

    std::unordered_map<std::string, Script> installed_scripts_map;
    std::unordered_map<std::string, Script> available_scripts_map;

public: 
    enum class Flag { list, install, uninstall, run };
    std::unordered_map<std::string, Flag> flag_map = {
        {"--list", Flag::list},
        {"--install", Flag::install},
        {"--uninstall", Flag::uninstall},
        {"--run", Flag::run},
    };

    std::unordered_map<std::string, Script> get_available_scripts_map() {
        for (Script script : database.available_scripts) {
            available_scripts_map[script.name] = script;
        }
        return available_scripts_map;
    }
    std::unordered_map<std::string, Script> get_installed_scripts_map() {
        for (Script script : installed_scripts) {
            installed_scripts_map[script.name] = script;
        }
        return installed_scripts_map;
    }

    int parse_command(Floorbot floorbot, std::string flag_input, std::string arg_input) {
        if (!flag_map.count(flag_input)) {
            std::cout << "Error: invalid flag entered." << std::endl;
            return 1;
        }
        Flag flag = flag_map[flag_input];
        std::string scriptname = arg_input;
        
        switch(flag) {
            case Flag::list:
                list();
                break;
            case Flag::install:
                install(scriptname);
                break;
            case Flag::uninstall:
                uninstall(scriptname);
                break;
            case Flag::run:
                run(scriptname);
                break;
        }
        return 0;
    }

    int list() {
        bool only_installed;
        if (installed_scripts.empty()) {
            std::cout << "No scripts are installed! Showing all scripts available for download:" << std::endl;
            only_installed = false;
        } else {
            std::cout << "List only installed scripts?" << std::endl;
            only_installed = utils.get_confirmation(false);
        };
        std::vector<Script> scripts_to_display;
        if (only_installed) {
            std::cout << std::endl << "Installed Scripts:" << std::endl;
            scripts_to_display = installed_scripts;
        } else {
            std::cout << "Available Scripts:" << std::endl;
            scripts_to_display = database.available_scripts;
        }

        int i = 1;
        for (Script script : scripts_to_display) {
            std::cout << std::to_string(i) << ". " << script.name << std::endl;
            i++;
        }
        return 0;
    }
    
    int install(std::string script_name) {
        if (!get_available_scripts_map().count(script_name)) {
            std::cout << "Error: script could not be located, is the script name correct?" << std::endl;
            return 1;
        }
        if (get_installed_scripts_map().count(script_name)) {
            std::cout << "Error: script is already installed!" << std::endl;
            return 1;
        }
        std::cout << "Installing " << script_name << "..." << std::endl;
        Script script_to_install = get_available_scripts_map()[script_name];
        get_installed_scripts_map()[script_name] = script_to_install;
        std::cout << script_name << " installed." << std::endl;
        return 0;
    }

    int uninstall(std::string script_name) {
        if (!get_installed_scripts_map().count(script_name)) {
            std::cout << "Error: script is not installed!" << std::endl;
            return 1;
        }
        std::cout << "Uninstalling " << script_name << "..."  << std::endl;
        get_installed_scripts_map().erase(script_name);
        std::cout << script_name << "uninstalled."  << std::endl;
        return 0;
    }

    int run(std::string script_name) {
        std::cout << "Searching for " << script_name << "..."  << std::endl;
        std::vector<std::string> command_set;
        bool script_found = false;
        for (Script script : database.available_scripts) {
            if (script.name == script_name) {
                command_set = script.command_set;
                script_found = true;
                break;
            }
        }
        if (!script_found) {
            std::cout << "Error: no script exists with the name '"
            << script_name << "'" << std::endl;
            return 1;
        }

        std::cout << script_name << " found, starting:" << std::endl;
        for (std::string command : command_set) {
            std::cout << command << std::endl;
        };
        std::cout << script_name << "finished."  << std::endl;
        return 0;
    }
};

#endif
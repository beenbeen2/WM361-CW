#ifndef SCRIPTSHANDLER
#define SCRIPTSHANDLER

#include "../services/CLICache.hpp"
#include "../services/AddOnsDatabase.hpp"
#include "../services/Database.hpp"
#include "../services/Utils.hpp"
#include "../services/Help.hpp"
  
class ScriptsHandler: virtual private CLICache {
private:
    AddOnsDatabase add_ons;
    Database database;
    Utils utils;
    Help help;

    std::unordered_map<std::string, std::shared_ptr<Script>> installed_scripts_map;
    std::unordered_map<std::string, std::shared_ptr<Script>> available_scripts_map;

    enum class Flag { list, install, uninstall, run, help };
    std::unordered_map<std::string, Flag> flag_map = {
        {"--list", Flag::list},
        {"--install", Flag::install},
        {"--uninstall", Flag::uninstall},
        {"--run", Flag::run},
        {"--help", Flag::help},
    };

    std::vector<std::shared_ptr<Script>> get_available_scripts() {
        std::vector<std::shared_ptr<Script>> available_scripts_refs;
        for (Script script : add_ons.available_scripts) {
            available_scripts_refs.push_back(std::make_shared<Script>(script));
        }
        return available_scripts_refs;
    }
    std::vector<std::shared_ptr<Script>> get_installed_scripts() {
        std::vector<std::shared_ptr<Script>> installed_scripts_refs;
        for (Script script : installed_scripts) {
            installed_scripts_refs.push_back(std::make_shared<Script>(script));
        }
        return installed_scripts_refs;
    }
    std::unordered_map<std::string, std::shared_ptr<Script>> get_available_scripts_map() {
        available_scripts_map.clear();
        for (std::shared_ptr<Script> script : get_available_scripts()) {
            available_scripts_map[script->name] = script;
        }
        return available_scripts_map;
    }
    std::unordered_map<std::string, std::shared_ptr<Script>> get_installed_scripts_map() {
        installed_scripts_map.clear();
        for (std::shared_ptr<Script> script : get_installed_scripts()) {
            installed_scripts_map[script->name] = script;
        }
        return installed_scripts_map;
    }

public:
    int parse_command(std::string flag_input, std::string arg_input) {
        if (!flag_map.count(flag_input)) {
            std::cerr << "Error: invalid flag entered." << std::endl << std::endl;
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
            case Flag::help:
                help.scripts();
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
        std::vector<std::shared_ptr<Script>> scripts_to_display;
        if (only_installed) {
            std::cout << std::endl << "Installed Scripts:" << std::endl;
            scripts_to_display = get_installed_scripts();
        } else {
            std::cout << "Available Scripts:" << std::endl;
            scripts_to_display = get_available_scripts();
        }

        int i = 1;
        for (std::shared_ptr<Script> script : scripts_to_display) {
            std::cout << std::to_string(i) << ". " << script->name << std::endl;
            i++;
        }
        std::cout << std::endl;
        return 0;
    }
    
    int install(std::string script_name) {
        if (!get_available_scripts_map().count(script_name)) {
            std::cerr << "Error: script could not be located, is the script name correct?" << std::endl << std::endl;
            return 1;
        }
        if (get_installed_scripts_map().count(script_name)) {
            std::cerr << "Error: script is already installed!" << std::endl << std::endl;
            return 1;
        }
        std::cout << "Installing " << script_name << "..." << std::endl;
        Script script_to_install = *get_available_scripts_map()[script_name];
        installed_scripts.push_back(script_to_install);
        std::cout << script_name << " installed." << std::endl << std::endl;
        return 0;
    }

    int uninstall(std::string script_name) {
        if (!get_installed_scripts_map().count(script_name)) {
            std::cerr << "Error: script is not installed!" << std::endl << std::endl;
            return 1;
        }
        std::cout << "Uninstalling " << script_name << "..."  << std::endl;
        Script script_to_uninstall = *get_available_scripts_map()[script_name];
        std::vector<Script>::iterator script_position = std::find(
            installed_scripts.begin(),
            installed_scripts.end(),
            script_to_uninstall
        );
        if (script_position == installed_scripts.end()) { 
            std::cerr << "Error: script could not be located." << std::endl << std::endl;
            return 1;
        }
        installed_scripts.erase(script_position); 
        std::cout << script_name << " uninstalled."  << std::endl << std::endl;
        return 0;
    }

    int run(std::string script_name) {
        std::cout << "Searching for " << script_name << "..."  << std::endl;
        if (!get_installed_scripts_map().count(script_name)) {
            std::cerr << "Error: script is not installed, is it spelt correctly?" << std::endl << std::endl;
            return 1;
        }
        std::vector<std::string> command_set;
        bool script_found = false;
        for (std::shared_ptr<Script> script : get_installed_scripts()) {
            if (script->name == script_name) {
                command_set = script->command_set;
                script_found = true;
                break;
            }
        }
        if (!script_found) {
            std::cerr << "Error: no script exists with the name '"
            << script_name << "', is" << std::endl  << std::endl;
            return 1;
        }

        std::cout << script_name << " found, starting script:" << std::endl << std::endl;
        for (std::string command : command_set) {
            std::cout << command << std::endl;
        };
        std::cout << std::endl;
        std::cout << script_name << " finished."  << std::endl << std::endl;
        return 0;
    }
};

#endif
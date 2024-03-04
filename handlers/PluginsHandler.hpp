#ifndef PLUGINSHANDLER
#define PLUGINSHANDLER

#include "../CLICache.hpp"
#include "../Database.hpp"
#include "../AddOnsDatabase.hpp"
#include "../Utils.hpp"

class PluginsHandler: virtual private CLICache {
private:
    AddOnsDatabase add_ons;
    Database database;
    Utils utils;

    std::unordered_map<std::string, std::shared_ptr<Plugin>> available_plugins_map;
    std::unordered_map<std::string, std::shared_ptr<Plugin>> installed_plugins_map;
    std::unordered_map<std::string, std::shared_ptr<Plugin>> enabled_plugins_map;

public:
    enum class Flag { list, install, uninstall, enable, disable, help };
    std::unordered_map<std::string, Flag> flag_map = {
        {"--list", Flag::list},
        {"--install", Flag::install},
        {"--uninstall", Flag::uninstall},
        {"--enable", Flag::enable},
        {"--disable", Flag::disable},
        {"--help", Flag::help},
    };

    std::vector<std::shared_ptr<Plugin>> get_available_plugins() {
        std::vector<std::shared_ptr<Plugin>> available_plugins_refs;
        for (Plugin plugin : add_ons.available_plugins) {
            available_plugins_refs.push_back(std::make_shared<Plugin>(plugin));
        }
        return available_plugins_refs;
    }
    std::vector<std::shared_ptr<Plugin>> get_installed_plugins() {
        std::vector<std::shared_ptr<Plugin>> installed_plugins_refs;
        for (Plugin plugin : current_floorbot->installed_plugins) {
            installed_plugins_refs.push_back(std::make_shared<Plugin>(plugin));
        }
        return installed_plugins_refs;
    }
    std::vector<std::shared_ptr<Plugin>> get_enabled_plugins() {
        std::vector<std::shared_ptr<Plugin>> enabled_plugins_refs;
        for (Plugin plugin : current_floorbot->installed_plugins) {
            if (plugin.enabled) {
                enabled_plugins_refs.push_back(std::make_shared<Plugin>(plugin));
            }
        }
        return enabled_plugins_refs;
    }
    std::unordered_map<std::string, std::shared_ptr<Plugin>> get_available_plugins_map() {
        available_plugins_map.clear();
        for (std::shared_ptr<Plugin> plugin : get_available_plugins()) {
            available_plugins_map[plugin->name] = plugin;
        }
        return available_plugins_map;
    }
    std::unordered_map<std::string, std::shared_ptr<Plugin>> get_installed_plugins_map() {
        installed_plugins_map.clear();
        for (std::shared_ptr<Plugin> plugin : get_installed_plugins()) {
            installed_plugins_map[plugin->name] = plugin;
        }
        return installed_plugins_map;
    }
    std::unordered_map<std::string, std::shared_ptr<Plugin>> get_enabled_plugins_map() {
        enabled_plugins_map.clear();
        for (std::shared_ptr<Plugin> plugin : get_enabled_plugins()) {
            enabled_plugins_map[plugin->name] = plugin;
        }
        return enabled_plugins_map;
    }

    int parse_command(std::string flag_input, std::string arg_input = "") {
        if (!flag_map.count(flag_input)) {
            std::cout << "Error: invalid flag entered."  << std::endl << std::endl;
            return 1;
        }
        Flag flag = flag_map[flag_input];

        std::string plugin_name = arg_input;
        switch(flag) {
            case Flag::list:
                list();
                break;
            case Flag::install:
                install(plugin_name);
                break;
            case Flag::uninstall:
                uninstall(plugin_name);
                break;
            case Flag::enable:
                enable(plugin_name);
                break;
            case Flag::disable:
                disable(plugin_name);
                break;
            case Flag::help:
                help();
                break;
        }
        return 0;
    };

    int list() {
        bool only_installed = false;
        bool only_enabled = false;
        if (get_installed_plugins_map().empty()) {
            std::cout << "No plugins are installed! Showing all plugins available for download." << std::endl << std::endl;
            only_installed = false;
            only_enabled = false;
        } else {
            std::cout << "List only installed plugins?" << std::endl;
            only_installed = utils.get_confirmation(false);

            if (only_installed) {
                std::cout << "List only the plugins that are currently enabled?" << std::endl;
                only_installed = utils.get_confirmation(false);
            }
        };
        std::vector<std::shared_ptr<Plugin>> plugins_to_display;
        if (only_enabled) {
            std::cout << std::endl << "Enabled Plugins:" << std::endl;
            plugins_to_display = get_enabled_plugins();
        } else if (only_installed) {
            std::cout << std::endl << "Installed Plugins:" << std::endl;
            plugins_to_display = get_installed_plugins();
        } else {
            std::cout << "Available Plugins:" << std::endl;
            plugins_to_display = get_available_plugins();
        }

        int i = 1;
        for (std::shared_ptr<Plugin> plugin : plugins_to_display) {
            std::cout << std::to_string(i) << ". " << plugin->name << std::endl;
            i++;
        }
        return 0;
    }

    int install(std::string plugin_name) {
        if (!get_available_plugins_map().count(plugin_name)) {
            std::cout << "Error: plugin could not be located, is the plugin name correct?" << std::endl << std::endl;
            return 1;
        }
        if (get_installed_plugins_map().count(plugin_name)) {
            std::cout << "Error: plugin is already installed!" << std::endl << std::endl;
            return 1;
        }
        std::cout << "Installing and enabling " << plugin_name << "..." << std::endl;
        Plugin plugin_to_install = *get_available_plugins_map()[plugin_name];
        current_floorbot->installed_plugins.push_back(plugin_to_install);
        std::cout << plugin_name << " installed and enabled." << std::endl << std::endl;
        return 0;
    }

    int uninstall(std::string plugin_name) {
        if (!get_installed_plugins_map().count(plugin_name)) {
            std::cout << "Error: plugin is not installed!" << std::endl << std::endl;
            return 1;
        }
        std::cout << "Uninstalling " << plugin_name << "..."  << std::endl;
        Plugin plugin_to_uninstall = *get_available_plugins_map()[plugin_name];
        std::vector<Plugin>::iterator plugin_position = std::find(
            current_floorbot->installed_plugins.begin(),
            current_floorbot->installed_plugins.end(),
            plugin_to_uninstall
        );
        if (plugin_position != current_floorbot->installed_plugins.end()) { 
            current_floorbot->installed_plugins.erase(plugin_position); 
        } else {
            std::cout << "Error: plugin could not be located." << std::endl << std::endl;
        }
        std::cout << plugin_name << " uninstalled and disabled."  << std::endl << std::endl;
        return 0;
    }

    int enable(std::string plugin_name) {
        if (!get_installed_plugins_map().count(plugin_name)) {
            std::cout << "Error: plugin is not installed!" << std::endl;
            return 1;
        }
        if (get_enabled_plugins_map().count(plugin_name)) {
            std::cout << "Error: plugin is already enabled!" << std::endl;
            return 1;
        }
        std::cout << "Enabling " << plugin_name << "..."  << std::endl;
        Plugin plugin_to_enable = *get_available_plugins_map()[plugin_name];
        plugin_to_enable.enabled = true;
        std::cout << plugin_name << " enabled."  << std::endl  << std::endl;
        return 0;
    }

    int disable(std::string plugin_name) {
        if (!get_installed_plugins_map().count(plugin_name)) {
            std::cout << "Error: plugin is not installed!" << std::endl << std::endl;
            return 1;
        }
        if (!get_enabled_plugins_map().count(plugin_name)) {
            std::cout << "Error: plugin is already disabled!" << std::endl << std::endl;
            return 1;
        }
        std::cout << "Disabling " << plugin_name << "..."  << std::endl;
        Plugin plugin_to_disable = *get_available_plugins_map()[plugin_name];
        plugin_to_disable.enabled = false;
        std::cout << plugin_name << "enabled."  << std::endl << std::endl;
        return 0;
    }

    void help() {
        std::cout << std::endl << "Available commands:" << std::endl;
        std::cout << "plugins" << std::endl
                  << "    --list" << std::endl
                  << "    --install <plugin-name>" << std::endl
                  << "    --uninstall <plugin-name>" << std::endl
                  << "    --enable <plugin-name>" << std::endl
                  << "    --disable <plugin-name>" << std::endl
                  << "    --help (display this message)" << std::endl << std::endl;
    }
};

#endif
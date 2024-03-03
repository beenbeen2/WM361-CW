#ifndef CLICACHE
#define CLICACHE

#include <memory>

#include "./components/Script.hpp"
#include "./components/Plugin.hpp"
#include "./components/Floorbot.hpp"
#include "./components/Account.hpp"

// In reality, scripts would be installed via the ScriptHandler and copied to the CLI Cache/local storage.
// However, for demonstration purposes they are simply composed directly from the Database class.
#include "AddOnsDatabase.hpp"
#include "Database.hpp"

class CLICache {
private:
    AddOnsDatabase add_ons;
    Database database;

public:
    static std::shared_ptr<Account> current_user;
    static std::shared_ptr<Floorbot> current_floorbot;
    static bool user_logged_in;
    static bool floorbot_selected;

    // "Pre-installing" all available scripts:
    std::vector<Script> installed_scripts = add_ons.available_scripts;

    // static std::shared_ptr<Account> get_current_user() { return current_user; }
    // static int set_current_user(std::shared_ptr<Account> selected_user) { 
    //     current_user = selected_user;
    //     return 1; 
    // }
    // static std::shared_ptr<Floorbot> get_current_floorbot() { return current_floorbot; }
    // static int set_current_floorbot(std::shared_ptr<Floorbot> selected_floorbot) { 
    //     current_floorbot = selected_floorbot;
    //     return 1; 
    // }
    // static bool get_user_logged_in() { return user_logged_in; }
    // static int set_user_logged_in(bool is_logged_in) { 
    //     user_logged_in = is_logged_in; 
    //     return 1;
    // }
    // static bool get_floorbot_selected() { return floorbot_selected; }
    // static int set_floorbot_selected(bool is_floorbot_selected) { 
    //     floorbot_selected = is_floorbot_selected;
    //     return 1;
    // }

};

#endif
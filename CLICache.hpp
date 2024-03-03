#ifndef CLICACHE
#define CLICACHE

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
    bool user_logged_in = false;
    std::shared_ptr<Account> current_user;
    bool floorbot_selected = false;
    std::shared_ptr<Floorbot> current_floorbot = database.;
    // "Pre-installing" all available scripts:
    std::vector<Script> installed_scripts = add_ons.available_scripts;
};

#endif
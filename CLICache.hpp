#ifndef CLICACHE
#define CLICACHE

#include "./components/Script.hpp"
#include "./components/Plugin.hpp"
#include "./components/Floorbot.hpp"
#include "./components/Account.hpp"

// In reality, scripts would be installed via the ScriptHandler and copied to the CLI Cache/local storage.
// However, for demonstration purposes they are simply composed directly from the Database class.
#include "Database.hpp"

class CLICache {
private:
    Database database;

public:
    bool user_logged_in = false;
    Account current_user;
    bool floorbot_selected = false;
    Floorbot current_floorbot;
    std::vector<Script> installed_scripts {
        database.shop_demo_script,
        database.snake_script
    };
};

#endif
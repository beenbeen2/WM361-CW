#include "CLICache.hpp"
#include "AddOnsDatabase.hpp"

AddOnsDatabase add_ons;

bool CLICache::floorbot_selected = false;
bool CLICache::user_logged_in = false;
std::shared_ptr<Floorbot> CLICache::current_floorbot = nullptr;
std::shared_ptr<Account> CLICache::current_user = nullptr;
std::vector<Script> installed_scripts =  add_ons.available_scripts;
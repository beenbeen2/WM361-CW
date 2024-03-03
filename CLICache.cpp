#include "CLICache.hpp"

bool CLICache::floorbot_selected = false;
bool CLICache::user_logged_in = false;
std::shared_ptr<Floorbot> CLICache::current_floorbot = nullptr;
std::shared_ptr<Account> CLICache::current_user = nullptr;
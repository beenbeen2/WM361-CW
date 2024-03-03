#ifndef ADDONSDATABASE
#define ADDONSDATABASE

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <memory>

#include "./components/Script.hpp"
#include "./components/Plugin.hpp"

class AddOnsDatabase {
    // Dummy plugins and scripts for demonstration purposes.
    // In reality, this would be a data layer interfacing with (potentially multiple)
    // databases, constructing and passing the requested objects on demand.
private:
    Script shop_demo_script = Script(
        "shop-demo-1",
        {"move --forward 5", "move --right 5", "move --back 5", "move --left 5"}
    );
    Script snake_script = Script(
        "snaking",
        {"move --forward 5", "move --right 5", "move --forward 5", "move left 5", "move --forward 5"}
    );

    Plugin eco_mode_plugin = Plugin("Eco-Mode", true);
    Plugin filter_warning_plugin = Plugin("Filter-Warning", true);

public:
    std::vector<Script> available_scripts { shop_demo_script, snake_script };
    std::vector<Plugin> available_plugins { eco_mode_plugin, filter_warning_plugin };
};

#endif
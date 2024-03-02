#ifndef DATABASE
#define DATABASE

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <chrono>
#include <fstream>

#include "./components/Script.hpp"
#include "./components/Plugin.hpp"
#include "./components/Floorbot.hpp"
#include "./components/Account.hpp"

class Database {
    // Dummy plugins and scripts
public:
    Script shop_demo_script = Script(
        "shop demo 1",
        {"move --forward 5", "move --right 5", "move --back 5", "move --left 5"}
    );

    Script snake_script = Script(
        "snaking",
        {"move --forward 5", "move --right 5", "move --forward 5", "move left 5", "move --forward 5"}
    );
    std::vector<Script> available_scripts {shop_demo_script, snake_script};

    Plugin eco_mode_plugin = Plugin("Eco Mode", true);
    Plugin filter_warning_plugin = Plugin("Filter Warning", true);

    std::vector<Plugin> available_plugins {eco_mode_plugin, filter_warning_plugin};

    Floorbot basic_fb1 = Floorbot(
        "Floorbot Mini Shop Demo 1",
        "Floorbot Mini",
        "R7L3X9Y2M6N1",
        "Z300",
        available_plugins
    );
    Floorbot basic_fb2 = Floorbot(
        "Downstairs Floorbot",
        "Floorbot Deluxe 4000",
        "Q8B4K6H2V5Z7",
        "X4000",
        available_plugins
    );
    Floorbot basic_fb3 = Floorbot(
        "Janet's Floorbot",
        "Floorbot Deluxe 4000",
        "F9T5C2V1J8P6",
        "X4000",
        available_plugins
    );

    std::vector<Floorbot> basic_floorbots = { basic_fb1, basic_fb2, basic_fb3  };

    Floorbot admin_fb1 = Floorbot(
        "Lab 433 Floorbot Pro",
        "Floorbot Pro 9000",
        "H5Y6M8J2R7Q1",
        "X9000",
        available_plugins
    );
    Floorbot admin_fb2 = Floorbot(
        "RDD Floorbot Pro No.32",
        "Floorbot Pro 9000",
        "P3N9X4K7D2W6",
        "X9000",
        available_plugins
    );
    Floorbot admin_fb3 = Floorbot(
        "'Unamed Floorbot 3'",
        "Floorbot Mini",
        "Z8O1T7V4B9S3",
        "Z300",
        available_plugins
    );
    std::vector<Floorbot> admin_floorbots = { admin_fb1, admin_fb2, admin_fb3  };

    // Dummy non-technical floorbots and users
    Account basic_account = Account("basic_user", false, basic_floorbots);

    // Dummy technical floorbots and users
    Account admin_account = Account("admin_user", true, admin_floorbots);
};

#endif
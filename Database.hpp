#ifndef DATABASE
#define DATABASE

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <memory>

#include "AddOnsDatabase.hpp"
#include "./components/Floorbot.hpp"
#include "./components/Account.hpp"

class Database {
    // Dummy floorbots and accounts for demonstration purposes.
    // In reality, this would be a data layer interfacing with (potentially multiple)
    // databases, constructing and passing the requested objects on demand.
private:
    AddOnsDatabase add_ons;
    std::vector<Plugin> plugins_copy;

    std::shared_ptr<Floorbot> basic_fb1 = std::make_shared<Floorbot>(
        "Floorbot Mini Shop Demo 1",
        "Floorbot Mini",
        "R7L3X9Y2M6N1",
        "Z300",
        plugins_copy
    );
    std::shared_ptr<Floorbot> basic_fb2 = std::make_shared<Floorbot>(
        "Downstairs Floorbot",
        "Floorbot Deluxe 4000",
        "Q8B4K6H2V5Z7",
        "X4000",
        plugins_copy
    );
    std::shared_ptr<Floorbot> basic_fb3 = std::make_shared<Floorbot>(
        "Janet's Floorbot",
        "Floorbot Deluxe 4000",
        "F9T5C2V1J8P6",
        "X4000",
        plugins_copy
    );
    std::shared_ptr<Floorbot> admin_fb1 = std::make_shared<Floorbot>(
        "Lab 433 Floorbot Pro",
        "Floorbot Pro 9000",
        "H5Y6M8J2R7Q1",
        "X9000",
        plugins_copy
    );
    std::shared_ptr<Floorbot> admin_fb2 = std::make_shared<Floorbot>(
        "RDD Floorbot Pro No.32",
        "Floorbot Pro 9000",
        "P3N9X4K7D2W6",
        "X9000",
        plugins_copy
    );
    std::shared_ptr<Floorbot> admin_fb3 = std::make_shared<Floorbot>(
        "'Unamed Floorbot 3'",
        "Floorbot Mini",
        "Z8O1T7V4B9S3",
        "Z300",
        plugins_copy
    );

public:
    std::vector<std::shared_ptr<Floorbot>> basic_floorbots = { basic_fb1, basic_fb2, basic_fb3  };
    std::vector<std::shared_ptr<Floorbot>> admin_floorbots = { admin_fb1, admin_fb2, admin_fb3  };
    Account basic_account = Account("basic_user", false, basic_floorbots);
    Account admin_account = Account("admin_user", true, admin_floorbots);
};

#endif
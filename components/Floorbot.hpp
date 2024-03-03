#ifndef FLOORBOT
#define FLOORBOT

#include <string>
#include <chrono>
#include <vector>
#include "Plugin.hpp"

class Floorbot {
private:
    bool is_floorbot_on = 1;

    std::string name, model, device_id, chipset, version;
    int bin_capacity, battery_level, battery_health, filter_health, power_usage;

    int major_version = 2, minor_version = 1, patch = 0;
    int x_coord = 0, y_coord = 0;

    std::chrono::system_clock::time_point start_time;
    std::chrono::system_clock::duration runtime;

public:
    std::vector<Plugin> installed_plugins {};
    std::vector<Plugin> enabled_plugins {};

    Floorbot() = default;

    Floorbot(
        std::string name,
        std::string model,
        std::string device_id,
        std::string chipset,
        std::vector<Plugin> installed_plugins
    ):
        name(name),
        model(model),
        device_id(device_id),
        chipset(chipset),
        installed_plugins(installed_plugins)
    {
        version = std::to_string(major_version) + "." + std::to_string(minor_version) + "." + std::to_string(patch);
        bin_capacity = rand() % 100 + 1;
        battery_level = rand() % 100 + 1;
        battery_health = rand() % 100 + 1;
        filter_health = rand() % 100 + 1;
        power_usage = rand() % 1000;
    }

    std::string get_name() const { return name; }
    std::string get_model() const { return model; }
    std::string get_device_id() const { return device_id; }
    std::string get_chipset() const { return chipset; }
    int get_x_coord() const { return x_coord; }
    int get_y_coord() const { return y_coord; }
    int get_bin_capacity() const { return bin_capacity; }
    int get_battery_level() const { return battery_level;}
    int get_battery_health() const { return battery_health; }
    int get_filter_health() const { return filter_health; }
    int get_power_usage() const { return power_usage; }

    std::chrono::system_clock::duration get_runtime() {
        std::chrono::system_clock::time_point current_time = std::chrono::system_clock::now();
        std::chrono::system_clock::duration runtime = std::chrono::duration(current_time - start_time);
        return runtime;
    }
    std::string get_version() {
        version = 
            std::to_string(major_version) + "." + 
            std::to_string(minor_version) + "." + 
            std::to_string(patch);
        return version;
    }
    
    int move_forward(int distance) {
        y_coord += distance;
        return 0;
    }
    int move_back(int distance) {
        y_coord -= distance;
        return 0;
    }
    int move_right(int distance) {
        x_coord += distance;
        return 0;
    }
    int move_left(int distance) {
        x_coord -= distance;
        return 0;
    }

    int power_on() {
        is_floorbot_on = 1;
        start_time = std::chrono::system_clock::now();
        return 0;
    }
    int power_off() { 
        is_floorbot_on = 0;
        power_on();
        return 0;
    }
    int restart() {
        power_off();
        power_on();        
        return 0;
    }
    int factory_reset() {
        major_version = 1;
        minor_version = 0;
        patch = 0;
        get_version();

        installed_plugins = {};
        restart();
        return 0;
    }
};

#endif
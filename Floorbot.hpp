#ifndef FLOORBOT
#define FLOORBOT

#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <vector>

class Floorbot {
private:
    std::string model;
    std::string device_id;
    std::string chipset;
    std::chrono::system_clock::time_point start_time;
    enum class MoveDirection { forward, back, right, left };

    int x_coord = 0;
    int y_coord = 0;
    int major_version = 2;
    int minor_version = 1;
    int patch = 0;

    std::chrono::system_clock::duration runtime;
    std::string version;
    int bin_capacity;
    int battery_level;
    int battery_health;
    int filter_health;
    int power_usage;

public:
    std::string name;

    Floorbot() = default;

    Floorbot(
        std::string name,
        std::string model,
        std::string device_id,
        std::string chipset
    ):
        name(name),
        model(model),
        device_id(device_id),
        chipset(chipset)

    {
        start_time = std::chrono::system_clock::now();
        version = std::to_string(major_version) + "." + std::to_string(minor_version) + "." + std::to_string(patch);
        bin_capacity = rand() % 100 + 1;
        battery_level = rand() % 100 + 1;
        battery_health = rand() % 100 + 1;
        filter_health = rand() % 100 + 1;
        power_usage = rand() % 1000;
    }

    std::chrono::system_clock::duration get_runtime() {
        std::chrono::system_clock::time_point current_time = std::chrono::system_clock::now();
        std::chrono::system_clock::duration runtime = std::chrono::duration(current_time - start_time);
        return runtime;
    }

    std::string get_version() { return version; }
    int get_bin_capacity() const { return bin_capacity; }
    int get_battery_level() const { return battery_level;}
    int get_battery_health() const { return battery_health; }
    int get_filter_health() const { return filter_health; }
    int get_power_usage() const { return power_usage; }

    int power_off() { return 0; }
    int restart() { return 0; }
    int factory_reset() { return 0; }
    
    int move(MoveDirection direction, int distance) {
        switch(direction) {
            case MoveDirection::forward:
                y_coord += distance;
                break;
            case MoveDirection::back:
                y_coord -= distance;
                break;
            case MoveDirection::left:
                x_coord += distance;
                break;
            case MoveDirection::right:
                x_coord -= distance;
                break;
        }
        std::cout << "Floorbot has moved " << distance << "cm to (" << x_coord << "," << y_coord << ").";
        return 0;
    }
};

#endif
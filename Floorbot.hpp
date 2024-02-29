#ifndef FLOORBOT
#define FLOORBOT

#include <iostream>
#include <string>
#include <chrono>
#include <thread>

class Floorbot {
public:
    Floorbot(
        std::string name,
        std::string model,
        std::string device_id,
        std::string chipset
    ):
        name(name),
        model(model),
        device_id(device_id),
        chipset(chipset),
        start_time(std::chrono::system_clock::now())
    {}

    std::string name;
    //  = "Unnamed Floorbot";
    std::string model;
    //  = "Floorbot Pro 9000";
    std::string device_id;
    //  = "DE9IL270QF9M";
    std::string chipset;
    //  = "X9000";
    std::chrono::system_clock::time_point start_time;

    enum class MoveDirection { forward, back, right, left };
    int x_coord = 0;
    int y_coord = 0;
    int major_version = 2;
    int minor_version = 1;
    int patch = 0;
    std::chrono::system_clock::duration runtime;

    std::string get_version() {
        std::string version = std::to_string(major_version) + "." + std::to_string(minor_version) + "." + std::to_string(patch);
        return version;
    }

    std::chrono::system_clock::duration get_runtime() {
        std::chrono::system_clock::time_point current_time = std::chrono::system_clock::now();
        std::chrono::system_clock::duration runtime = chrono::duration(current_time - start_time);
        return runtime;
    }

    int get_bin_capacity() {
        int bin_capacity = rand() % 100 + 1;
        return bin_capacity;
    }

    int get_battery_level() {
        int battery_level = rand() % 100 + 1;
        return battery_level;
    }

    int get_battery_health() {
        int battery_health = rand() % 100 + 1;
        return battery_health;
    }

    int get_filter_health() {
        int filter_health = rand() % 100 + 1;
        return filter_health;
    }

    int get_power_usage() {
        int power_usage = rand() % 1000;
        return power_usage;
    }

    int power_off() {
    }

    int restart() {

    }

    int factory_reset() {

    }
    
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
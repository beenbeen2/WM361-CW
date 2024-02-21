#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

class Robot {
    public:
        string name = "Unnamed Floorbot";
        string model = "Floorbot Pro 9000";
        string device_id = "DE9IL270QF9M";
        string chipset = "X9000";

        int major_version = 2;
        int minor_version = 1;
        int patch = 0;

        const chrono::system_clock::time_point start_time = std::chrono::system_clock::now();
        chrono::system_clock::duration runtime;

        string get_version() {
            string version = std::to_string(major_version) + "." + std::to_string(minor_version) + "." + std::to_string(patch);
            return version;
        }

        chrono::system_clock::duration get_runtime() {
            chrono::system_clock::time_point current_time = std::chrono::system_clock::now();
            chrono::system_clock::duration runtime = chrono::duration(current_time - start_time);
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
        
        int move(string direction, int distance) {

        }

        int rotate(string direction, int angle) {
            
        }
};

int main() {
    cout << "\n\n\n\nStarting!\n\n";

    Robot Robot;
    cout << "Robot name is '" << Robot.name << "'\n";
    cout << "Robot model is '" << Robot.model << "'\n";
    cout << "Robot is on version " << Robot.get_version() << "\n";
    cout << "Robot chipset is '" << Robot.chipset << "'\n";
    cout << "Robot bin capacity is " << Robot.get_bin_capacity() << "%\n";
    cout << "Robot battery level is " << Robot.get_battery_level() << "%\n";
    cout << "Robot battery health is " << Robot.get_battery_health() << "%\n";
    cout << "Robot filter health is " << Robot.get_filter_health() << "%\n";
    cout << "Robot power usage is " << Robot.get_power_usage() << "W\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    chrono::system_clock::duration runtime = Robot.get_runtime();
    cout << "Robot has been running for " << runtime.count() << "ns";

    cout << "\n\nDone! \n\n\n";
    return 1;
};
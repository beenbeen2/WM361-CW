#ifndef DIAGNOSTICS
#define DIAGNOSTICS

class Diagnostics {
public:
    enum class Flag { print, save, submit };
    std::unordered_map<std::string, Flag> flag_map = {
        {"--print", Flag::print},
        {"--save", Flag::save},
        {"--submit", Flag::submit},
    };

    int parse_command(Floorbot floorbot, std::string flag_input, std::string arg_input = "") {
        if (!flag_map.count(flag_input)) {
            std::cout << "Error: invalid direction flag entered.";
            return 1;
        }
        Flag flag = flag_map[flag_input];

        switch(flag) {
            case Flag::print:
                print(floorbot);
                break;
            case Flag::save:
                if (arg_input.empty()) {
                    std::cout << "Error: Please provide a filename to save the diagnostic report to.";
                    return 1;
                }
                save(floorbot, arg_input);
                break;
            case Flag::submit:
                submit(floorbot);
                break;
        }
        return 0;
    }

    int print(Floorbot floorbot) {
        std::cout 
            << std::endl << "DIAGNOSTIC REPORT" << std::endl,
            << "Name: '" << floorbot.get_name() << "'" << std::endl,
            << "Model " << floorbot.get_model() << std::endl,
            << "ID: " << floorbot.get_device_id() << std::endl,
            << "Chipset: " << floorbot.get_chipset() << std::endl,
            o::system_clock::duration runtime = floorbot.get_runtime(),
            << "Session Runtime: " << runtime.count() << "ns",
            << "Firmware Version: " << floorbot.get_version() << "" << std::endl,
            << "Bin capacity: " << floorbot.get_bin_capacity() << "%" << std::endl,
            << "Battery: " << floorbot.get_battery_level() << "%" << std::endl,
            << "Battery health: " << floorbot.get_battery_health() << "%" << std::endl,
            << "Filter health: " << floorbot.get_filter_health() << "%" << std::endl,
            << "Power Usage: " << floorbot.get_power_usage() << "W" << std::endl,
            << std::endl;
        return 0;
    }

    int save(Floorbot floorbot, std::string filename) {
        std::cout 
            << "Diagnostic report for " << floorbot.get_name() 
            << " has successfully been saved to" << filename << ".txt" << std::endl;
        return 0;
    }

    int submit(Floorbot floorbot) {
        std::cout 
            << "Diagnostic report for " << floorbot.get_name() 
            << " has successfully been submitted to Floorbot customer support." << std::endl;
        return 0;
    }
};

#endif
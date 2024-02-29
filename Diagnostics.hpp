#ifndef DIAGNOSTICS
#define DIAGNOSTICS

class Diagnostics {
public:
    enum class Flag { print, save, submit };
    std::unordered_map<std::string, Flag> diagnostics_flag_map = {
        {"--print", Flag::print},
        {"--save", Flag::save},
        {"--submit", Flag::submit},
    };

    int parse_command(Floorbot floorbot, std::string flag_input, std::string arg_input = "") {
        if (!diagnostics_flag_map.count(flag_input)) {
            std::cout << "Error: invalid direction flag entered.";
            return 1;
        }
        Flag flag = diagnostics_flag_map[flag_input];

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
        std::cout << "floorbot name is '" << floorbot.get_name() << "'" << std::endl;
        std::cout << "floorbot model is '" << floorbot.get_model() << "'" << std::endl;
        std::cout << "floorbot id is '" << floorbot.get_device_id() << "'" << std::endl;
        std::cout << "floorbot chipset is '" << floorbot.get_chipset() << "'" << std::endl;
        std::chrono::system_clock::duration runtime = floorbot.get_runtime();
        std::cout << "Robot has been running for " << runtime.count() << "ns";
        std::cout << "floorbot is on version " << floorbot.get_version() << "" << std::endl;
        std::cout << "floorbot bin capacity is " << floorbot.get_bin_capacity() << "%" << std::endl;
        std::cout << "floorbot battery level is " << floorbot.get_battery_level() << "%" << std::endl;
        std::cout << "floorbot battery health is " << floorbot.get_battery_health() << "%" << std::endl;
        std::cout << "floorbot filter health is " << floorbot.get_filter_health() << "%" << std::endl;
        std::cout << "floorbot power usage is " << floorbot.get_power_usage() << "W" << std::endl;
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
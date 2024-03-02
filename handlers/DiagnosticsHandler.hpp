#ifndef DIAGNOSTICSHANDLER
#define DIAGNOSTICSHANDLER

#include "../CLICache.hpp"
#include "../Database.hpp"
#include "../Utils.hpp"

class DiagnosticsHandler: virtual private CLICache {
private:
    Database database;
    Utils utils;
    std::string file_extension = ".txt";

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
                    std::cout << "Error: Please provide a filename to save the diagnostic report to." << std::endl;
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
        std::chrono::_V2::system_clock::duration runtime = floorbot.get_runtime();

        std::cout << std::endl << "DIAGNOSTIC REPORT" << std::endl;
        std::cout << "Name: '" << floorbot.get_name() << "'" << std::endl;
        std::cout << "Model " << floorbot.get_model() << std::endl;
        std::cout << "ID: " << floorbot.get_device_id() << std::endl;
        std::cout << "Chipset: " << floorbot.get_chipset() << std::endl;
        std::cout << "Session Runtime: " << runtime.count() << "ns" << std::endl;
        std::cout << "Firmware Version: " << floorbot.get_version() << "" << std::endl;
        std::cout << "Bin capacity: " << floorbot.get_bin_capacity() << "%" << std::endl;
        std::cout << "Battery: " << floorbot.get_battery_level() << "%" << std::endl;
        std::cout << "Battery health: " << floorbot.get_battery_health() << "%" << std::endl;
        std::cout << "Filter health: " << floorbot.get_filter_health() << "%" << std::endl;
        std::cout << "Power Usage: " << floorbot.get_power_usage() << "W" << std::endl;
        std::cout << std::endl;
        return 0;
    }

    int save(Floorbot floorbot, std::string filename) {
        // if ((filename.length() < file_extension.length()) {
        //     std::cout << "Error: file name must include a support type extension, such as '.txt'." << std::endl;
        //     return 1;
        // }
        // if (filename.substr(filename.length() - file_extension.length()) == file_extension)) {
        //     std::cout << "Error: Unsupported file type, filename must end in '.txt'." << std::endl;
        //     return 1;
        // }
        std::string file_path = ".\\saved_reports\\" + filename + file_extension;
        std::ofstream DiagnosticReport(file_path);

        if (!DiagnosticReport.is_open()) {
            std::cout << "Error: Failed to open file for writing, check the filename entered is valid." << std::endl;
            return 1;
        }

        std::chrono::_V2::system_clock::duration runtime = floorbot.get_runtime();
        DiagnosticReport << std::endl << "DIAGNOSTIC REPORT" << std::endl;
        DiagnosticReport << "Name: '" << floorbot.get_name() << "'" << std::endl;
        DiagnosticReport << "Model " << floorbot.get_model() << std::endl;
        DiagnosticReport << "ID: " << floorbot.get_device_id() << std::endl;
        DiagnosticReport << "Chipset: " << floorbot.get_chipset() << std::endl;
        DiagnosticReport << "Session Runtime: " << runtime.count() << "ns" << std::endl;
        DiagnosticReport << "Firmware Version: " << floorbot.get_version() << "" << std::endl;
        DiagnosticReport << "Bin capacity: " << floorbot.get_bin_capacity() << "%" << std::endl;
        DiagnosticReport << "Battery: " << floorbot.get_battery_level() << "%" << std::endl;
        DiagnosticReport << "Battery health: " << floorbot.get_battery_health() << "%" << std::endl;
        DiagnosticReport << "Filter health: " << floorbot.get_filter_health() << "%" << std::endl;
        DiagnosticReport << "Power Usage: " << floorbot.get_power_usage() << "W" << std::endl;

        DiagnosticReport.close();
        std::cout 
            << "Diagnostic report for " << floorbot.get_name() 
            << " has successfully been saved to " << file_path << std::endl;
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
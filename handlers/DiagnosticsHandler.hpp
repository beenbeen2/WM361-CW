#ifndef DIAGNOSTICSHANDLER
#define DIAGNOSTICSHANDLER

#include "../CLICache.hpp"
#include "../Database.hpp"
#include "../Utils.hpp"

class DiagnosticsHandler: virtual private CLICache {
private:
    Database database;
    Utils utils;
    const std::string file_extension = ".txt";
    enum class Flag { print, save, submit, help };
    const std::unordered_map<std::string, const Flag> flag_map = {
        {"--print", Flag::print},
        {"--save", Flag::save},
        {"--submit", Flag::submit},
        {"--help", Flag::help},
    };

public:
    int parse_command(std::string flag_input, std::string arg_input = "") {
        if (!flag_map.count(flag_input)) {
            std::cout << "Error: invalid flag entered." << std::endl << std::endl;
            return 1;
        }
        Flag flag = flag_map.at(flag_input);

        std::string file_name = arg_input;
        switch(flag) {
            case Flag::print:
                print();
                break;
            case Flag::save:
                if (arg_input.empty()) {
                    std::cout << "Error: Please provide a filename to save the diagnostic report to." << std::endl << std::endl;
                    return 1;
                }
                save(file_name);
                break;
            case Flag::submit:
                submit();
                break;
            case Flag::help:
                help();
                break;
        }
        return 0;
    }

    int print() {
        std::chrono::_V2::system_clock::duration runtime = current_floorbot->get_runtime();

        std::cout << std::endl << "DIAGNOSTIC REPORT" << std::endl;
        std::cout << "Name: '" << current_floorbot->get_name() << "'" << std::endl;
        std::cout << "Model " << current_floorbot->get_model() << std::endl;
        std::cout << "Firmware Version: " << current_floorbot->get_version() << "" << std::endl;
        if (current_user->is_admin) {
            std::cout << "ID: " << current_floorbot->get_device_id() << std::endl;
            std::cout << "Chipset: " << current_floorbot->get_chipset() << std::endl;
            std::cout << "Session Runtime: " << runtime.count() << "ns" << std::endl;
            std::cout << "Power Usage: " << current_floorbot->get_power_usage() << "W" << std::endl;
            std::cout << "Battery health: " << current_floorbot->get_battery_health() << "%" << std::endl;
        }
        std::cout << "Battery level: " << current_floorbot->get_battery_level() << "%" << std::endl;
        std::cout << "Bin capacity: " << current_floorbot->get_bin_capacity() << "%" << std::endl;
        std::cout << "Filter health: " << current_floorbot->get_filter_health() << "%" << std::endl;
        std::cout << std::endl;
        return 0;
    }

    int save(std::string filename) {
        // if ((filename.length() < file_extension.length()) {
        //     std::cout << "Error: file name must include a support type extension, such as '.txt'." << std::endl;
        //     return 1;
        // }
        // if (filename.substr(filename.length() - file_extension.length()) == file_extension)) {
        //     std::cout << "Error: Unsupported file type, filename must end in '.txt'." << std::endl;
        //     return 1;
        // }
        std::string file_path = "saved_reports\\" + filename + file_extension;
        std::ofstream DiagnosticReport(file_path);

        if (!DiagnosticReport.is_open()) {
            std::cout << "Error: Failed to open file for writing, check the filename entered is valid." << std::endl << std::endl;
            return 1;
        }

        std::chrono::_V2::system_clock::duration runtime = current_floorbot->get_runtime();
        DiagnosticReport << std::endl << "DIAGNOSTIC REPORT" << std::endl;
        DiagnosticReport << "Name: '" << current_floorbot->get_name() << "'" << std::endl;
        DiagnosticReport << "Model " << current_floorbot->get_model() << std::endl;
        DiagnosticReport << "Firmware Version: " << current_floorbot->get_version() << "" << std::endl;
        if (current_user->is_admin) {
            DiagnosticReport << "ID: " << current_floorbot->get_device_id() << std::endl;
            DiagnosticReport << "Chipset: " << current_floorbot->get_chipset() << std::endl;
            DiagnosticReport << "Session Runtime: " << runtime.count() << "ns" << std::endl;
            DiagnosticReport << "Power Usage: " << current_floorbot->get_power_usage() << "W" << std::endl;
            DiagnosticReport << "Battery health: " << current_floorbot->get_battery_health() << "%" << std::endl;
        }
        DiagnosticReport << "Battery level: " << current_floorbot->get_battery_level() << "%" << std::endl;
        DiagnosticReport << "Bin capacity: " << current_floorbot->get_bin_capacity() << "%" << std::endl;
        DiagnosticReport << "Filter health: " << current_floorbot->get_filter_health() << "%" << std::endl;

        DiagnosticReport.close();
        std::cout 
            << "The diagnostic report for " << current_floorbot->get_name() 
            << " has successfully been saved to " << file_path << std::endl << std::endl;
        return 0;
    }

    int submit() {
        std::cout 
            << "The diagnostic report for " << current_floorbot->get_name() 
            << " has successfully been submitted to Floorbot customer support." << std::endl << std::endl;
        return 0;
    }

    void help() {
        std::cout << std::endl << "Available commands:" << std::endl;
        std::cout << "diagnostics" << std::endl
                  << "    --print" << std::endl
                  << "    --save <filename>" << std::endl
                  << "    --submit" << std::endl
                  << "    --help (display this message)" << std::endl << std::endl;
    }
};

#endif
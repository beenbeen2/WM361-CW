#ifndef COMMANDPARSER
#define COMMANDPARSER

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <sstream>
#include "Floorbot.hpp"
#include "Account.hpp"
#include "Move.hpp"
#include "Diagnostics.hpp"
#include "Scripts.hpp"
#include "Plugins.hpp"

class CommandHandler {
public:
    CommandHandler() = default;

    Move move;
    Diagnostics diagnostics;

    enum class Command { move, diagnostics, plugins, scripts, control, help };
    std::unordered_map<std::string, Command> command_map = {
        {"move", Command::move},
        {"diagnostics", Command::diagnostics},
        {"plugins", Command::plugins},
        {"scripts", Command::scripts},
        {"control", Command::control},
        {"--help", Command::help},
    };

    int parse_command(
        std::string command_input,
        std::string flag_input,
        std::string arg_input = "",
        Floorbot floorbot
    ) {
        if (!command_map.count(command_input)) {
            std::cout << "Error: invalid command entered.";
            return 1;
        }
        Command command = command_map[command_input];

        switch(command) {
            case Command::move: 
                move.parse_move(floorbot, flag_input, arg_input);
                break;
            case Command::diagnostics:
                if (!diagnostics_flag_map.count(flag_input)) {
                    std::cout << "Error: invalid direction flag entered.";
                    return 1;
                }
                Diagnostics::Flag flag = diagnostics_flag_map[flag_input];
                handle_diagnostics(flag);
                break;
            case Command::plugins:
                handle_plugin();
                break;
            case Command::scripts:
                handle_script();
                break;
            case Command::control:
                handle_control();
                break;
            case Command::help:
                handle_control();
                break;
        }

        return 0;
    };

    int handle_diagnostics(Diagnostics::Flag flag, std::string filename = "") {
        if (flag == Diagnostics::Flag::print) {
            diagnostics.print(floorbot);
            return 0;
        }
        if (flag == Diagnostics::Flag::save) {
            if (filename.empty()) {
                std::cout << "Error: Please provide a filename to save the diagnostic report to.";
                return 1;
            }
            diagnostics.save(floorbot, filename);
            return 0;
        }
        if (flag == Diagnostics::Flag::submit) {
            diagnostics.submit(floorbot);
            return 0;
        }
        return 1;
    }

};

#endif
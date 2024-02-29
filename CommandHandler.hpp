#ifndef COMMANDPARSER
#define COMMANDPARSER

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include "Floorbot.hpp"
#include "Account.hpp"
#include "Diagnostics.hpp"

class CommandHandler {
public:
    CommandHandler() = default;

    enum class Command { move, diagnostics, plugins, scripts, robot };
    std::unordered_map<std::string, Command> command_map = {
        {"move", Command::move},
        {"diagnostics", Command::diagnostics},
        {"plugins", Command::plugins},
        {"scripts", Command::scripts},
        {"robot", Command::robot},
    };

    enum class DiagnosticsFlag { print, save, submit };
    std::unordered_map<std::string, DiagnosticsFlag> diagnostic_flag_map = {
        {"--print", DiagnosticsFlag::print},
        {"--save", DiagnosticsFlag::save},
        {"--submit", DiagnosticsFlag::submit},
    };

    enum class ScriptFlag { list, install, uninstall, run };
    std::unordered_map<std::string, ScriptFlag> script_flag_map = {
        {"--list", ScriptFlag::list},
        {"--install", ScriptFlag::install},
        {"--uninstall", ScriptFlag::uninstall},
        {"--submit", ScriptFlag::run},
    };

    enum class PluginFlag { list, install, uninstall, enable, disable };
    std::unordered_map<std::string, PluginFlag> plugin_flag_map = {
        {"--list", PluginFlag::list},
        {"--install", PluginFlag::install},
        {"--uninstall", PluginFlag::uninstall},
        {"--enable", PluginFlag::enable},
        {"--disable", PluginFlag::disable},
    };

    int handle_move(Floorbot floorbot, Floorbot::MoveFlag flag, int distance) {

        floorbot.move(flag, distance);

        return 0;
    }

    int handle_diagnostics(Floorbot floorbot, Diagnostics::Flag flag, int distance) {

        floorbot.move(flag, distance);

        return 0;
    }

};

#endif
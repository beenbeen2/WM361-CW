#ifndef HELP
#define HELP

#include <iostream>

class Help {
public:
    void general() {
        std::cout << "Commands take the form: 'command --flag <argument>'" << std::endl;
        std::cout << "and you can type EXIT at any time to exit the CLI." << std::endl << std::endl;
    }
    void move() {
        std::cout << "move " << std::endl;
        std::cout << "    --forward <distance>" << std::endl
                  << "    --back <distance>" << std::endl
                  << "    --right <distance>" << std::endl
                  << "    --left <distance>" << std::endl
                  << "    --help" << std::endl
                  << std::endl;
    }
    void diagnostics() {
        std::cout << "diagnostics" << std::endl
                  << "    --print" << std::endl
                  << "    --save <filename>" << std::endl
                  << "    --submit" << std::endl
                  << "    --help" << std::endl
                  << std::endl;
    }
    void plugins() {
        std::cout << "plugins" << std::endl
                  << "    --list" << std::endl
                  << "    --install <plugin-name>" << std::endl
                  << "    --uninstall <plugin-name>" << std::endl
                  << "    --enable <plugin-name>" << std::endl
                  << "    --disable <plugin-name>" << std::endl
                  << "    --help" << std::endl
                  << std::endl;
    }
    void scripts() {
        std::cout << "scripts" << std::endl
                  << "    --list" << std::endl
                  << "    --install <script-name>" << std::endl
                  << "    --uninstall <script-name>" << std::endl
                  << "    --run <script-name>" << std::endl
                  << "    --help" << std::endl
                  << std::endl;
    }
    void control() {
        std::cout << "control" << std::endl
                  << "    --restart" << std::endl
                  << "    --power_off" << std::endl
                  << "    --power_on" << std::endl
                  << "    --factory_reset" << std::endl
                  << "    --help" << std::endl
                  << std::endl;
    }
};

#endif
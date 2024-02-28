#include <iostream>
#include <string>
#include <unordered_map>

class CommandParser {
public:    
    enum class command { move, diagnostics, plugins, scripts, robot };

    std::unordered_map<std::string, command> input_map = {
        {"move", command::move},
        {"diagnostics", command::diagnostics},
        {"plugins", command::plugins},
        {"scripts", command::scripts},
        {"robot", command::robot},
    };

    int input(std::string input) {
        if (!input_map.count(input)) {
            std::cout << "Error: invalid command entered.";
            return 1;
        }

        command user_command = input_map[input];
        switch( user_command ) {
            case command::move: 
                move();
            case command::diagnostics:
                diagnostics();
            case command::plugins:
                plugins();
            case command::scripts:
                scripts();
            case command::robot:
                robot();
        }

        return 0;
    }
};

int main () {
    CommandParser parse;
    std::string input;

    std::cout << "Enter a command:\n";
    std::cin >> input;
    parse.input(input);

    return 0;
};
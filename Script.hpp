#ifndef SCRIPT
#define SCRIPT

#include <vector>

class Script {
public:
    Script(
        std::string name,
        std::vector<std::string> command_set
    ):
        name(name),
        command_set(command_set)
    {}

    std::string name;
    std::vector<std::string> command_set;
};

#endif
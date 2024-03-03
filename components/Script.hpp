#ifndef SCRIPT
#define SCRIPT

#include <string>
#include <vector>

class Script {
public:
    Script() = default;
    Script(
        std::string name,
        std::vector<std::string> command_set
    ):
        name(name),
        command_set(command_set)
    {}

    std::string name;
    std::vector<std::string> command_set;

    bool operator==(const Script& other_script) const {
        return name == other_script.name;
    }
};

#endif
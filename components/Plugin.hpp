#ifndef PLUGIN
#define PLUGIN

#include <string>

class Plugin {
public:
    Plugin() = default;
    Plugin(
        std::string name,
        bool enabled
    ):
        name(name),
        enabled(enabled)
    {};
    
    std::string name;
    bool enabled;

    bool operator==(const Plugin& other_plugin) const {
        return name == other_plugin.name;
    }
};

#endif
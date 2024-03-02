#ifndef PLUGIN
#define PLUGIN

#include <string>

class Plugin {
public:
    Plugin(
        std::string name,
        bool enabled
    ):
        name(name),
        enabled(enabled)
    {};
    
    std::string name;
    bool enabled;
};

#endif
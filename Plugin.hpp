#ifndef PLUGIN
#define PLUGIN

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


class Control {
public:
    enum class Flag { restart, shutdown, factory_reset };
    std::unordered_map<std::string, Flag> control_flag_map = {
        {"--restart", Flag::restart},
        {"--shutdown", Flag::shutdown},
        {"--factory_reset", Flag::factory_reset},
    };

    int parse_command(Floorbot floorbot, std::string flag_input, std::string arg_input = "") {

    };
};
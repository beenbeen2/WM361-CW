

class Control {
    enum class Flag { restart, shutdown, factory_reset };
    std::unordered_map<std::string, Flag> control_flag_map = {
        {"--restart", Flag::restart},
        {"--shutdown", Flag::shutdown},
        {"--factory_reset", Flag::factory_reset},
    };
}
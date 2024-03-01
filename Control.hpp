#ifndef CONTROL
#define CONTROL

class Control {
public:
    enum class Flag { restart, shutdown, factory_reset };
    std::unordered_map<std::string, Flag> flag_map = {
        {"--restart", Flag::restart},
        {"--power_off", Flag::shutdown},
        {"--factory_reset", Flag::factory_reset},
    };

    int parse_command(Floorbot floorbot, std::string flag_input, std::string arg_input = "") {
        if (!flag_map.count(flag_input)) {
            std::cout << "Error: invalid flag entered.";
            return 1;
        }
        Flag flag = flag_map[flag_input];
        
        switch(flag) {
            case Flag::restart:
                restart(floorbot);
                break;
            case Flag::shutdown:
                power_off(floorbot);
                break;
            case Flag::factory_reset:
                factory_reset(floorbot);
                break;
        }
        return 0;
    };

    int restart(Floorbot floorbot) {
        std::cout << "Restarting " << floorbot.get_name() << "...";
        floorbot.restart();
        return 0;
    };

    int power_off(Floorbot floorbot) {
        std::cout << "Turning " << floorbot.get_name() << " off...";
        floorbot.power_off();
        // select another robot?
        return 0;
    };

    int factory_reset(Floorbot floorbot) {
        // add confirmation?
        floorbot.factory_reset();
        // select another robot?
        return 0;
    };
};

#endif
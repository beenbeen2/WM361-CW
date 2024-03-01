#ifndef SCRIPTS
#define SCRIPTS
  
class Scripts {
public:
    DummyObjects dummy_objects;
    enum class Flag { list, install, uninstall, run };
    std::unordered_map<std::string, Flag> flag_map = {
        {"--list", Flag::list},
        {"--install", Flag::install},
        {"--uninstall", Flag::uninstall},
        {"--run", Flag::run},
    };

    std::vector<Script> installed_scripts {};

    int parse_command(Floorbot floorbot, std::string flag_input, std::string arg_input) {
        if (!flag_map.count(flag_input)) {
            std::cout << "Error: invalid flag entered.";
            return 1;
        }
        Flag flag = flag_map[flag_input];
        
        switch(flag) {
            case Flag::list:
                bool only_installed;
                istringstream(arg_input) >> only_installed;
                list();
                break;
            case Flag::install:
                install();
                break;
            case Flag::uninstall:
                uninstall();
                break;
            case Flag::run:
                run();
                break;
        }
        return 0;
    }

    int list(bool only_installed) {
        if (only_installed) {
            int i = 1;
            for (Script script : installed_scripts) {
                std::cout << std::to_string(i) << ". " << script.name << std::endl;
                i++;
            }
        }
        return 0;
    }
    
    int install(std::string scriptname) {
        std::cout << "Installing " << scriptname << "..." << std::endl;
        return 0;
    }

    int uninstall(std::string scriptname) {
        std::cout << "Uninstalling " << scriptname << "..."  << std::endl;
        return 0;
    }

    int run(std::string scriptname) {
        std::cout << "Running " << scriptname << "..."  << std::endl;
        return 0;
    }
};

#endif
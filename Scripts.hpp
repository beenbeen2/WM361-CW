#ifndef SCRIPTS
#define SCRIPTS
  
class Scripts {
public:
    DummyObjects dummy_objects;
    enum class Flag { list, install, uninstall, run };
    std::unordered_map<std::string, Flag> script_flag_map = {
        {"--list", Flag::list},
        {"--install", Flag::install},
        {"--uninstall", Flag::uninstall},
        {"--run", Flag::run},
    };

    std::vector<Script> installed_scripts {};

    int parse_command(Floorbot floorbot, std::string flag_input, std::string arg_input) {

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
    
    int install() {
        
        return 0;
    }

    int uninstall() {
        
        return 0;
    }

    int run() {
        
        return 0;
    }
};

#endif
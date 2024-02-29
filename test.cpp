#include "Floorbot.hpp"
#include "Account.hpp"
// #include "DummyObjects.hpp"


int main() {
    // Floorbot dummy_floorbot2 = Floorbot(
    //     "Floorbot Mini Shop Demo 1",
    //     "Floorbot Mini",
    //     "R7L3X9Y2M6N1",
    //     "Z300"
    // );

    // std::cout << dummy_floorbot2.name;

    Floorbot basic_fb1 = Floorbot(
        "Floorbot Mini Shop Demo 1",
        "Floorbot Mini",
        "R7L3X9Y2M6N1",
        "Z300"
    );
    Floorbot basic_fb2 = Floorbot(
        "Downstairs Floorbot",
        "Floorbot Deluxe 4000",
        "Q8B4K6H2V5Z7",
        "X4000"
    );
    Floorbot basic_fb3 = Floorbot(
        "Janet's Floorbot",
        "Floorbot Deluxe 4000",
        "F9T5C2V1J8P6",
        "X4000"
    );
    std::vector<Floorbot> basic_linked_floorbots = { basic_fb1, basic_fb2, basic_fb3  };
    Account basic_account = Account("basic_user", false, basic_linked_floorbots);

    return 0;
}
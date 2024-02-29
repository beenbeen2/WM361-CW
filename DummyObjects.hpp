#ifndef DUMMYOBJECTS
#define DUMMYOBJECTS

#include "Floorbot.hpp"
#include "Account.hpp"

class DummyObjects {
public:
// Dummy non-technical floorbots and users
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

// Dummy technical floorbots and users
    Floorbot admin_fb1 = Floorbot(
        "Lab 433 Floorbot Pro",
        "Floorbot Pro 9000",
        "H5Y6M8J2R7Q1",
        "X9000"
    );
    Floorbot admin_fb2 = Floorbot(
        "RDD Floorbot Pro No.32",
        "Floorbot Pro 9000",
        "P3N9X4K7D2W6",
        "X9000"
    );
    Floorbot admin_fb3 = Floorbot(
        "'Unamed Floorbot 3'",
        "Floorbot Mini",
        "Z8O1T7V4B9S3",
        "Z300"
    );
    std::vector<Floorbot> admin_linked_floorbots = { admin_fb1, admin_fb2, admin_fb3  };
    Account admin_account = Account("admin_user", true, admin_linked_floorbots);

    DummyObjects() = default;
};

#endif
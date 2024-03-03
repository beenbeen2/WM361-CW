#ifndef ACCOUNT
#define ACCOUNT

#include <memory>

class Account {
public:
    Account() = default;
    Account(
        std::string username,
        bool is_admin,
        std::vector<std::shared_ptr<Floorbot>> linked_floorbots
    ): 
        username(username),
        is_admin(is_admin),
        linked_floorbots(linked_floorbots)
    {}

    const std::string username;
    bool is_admin;
    const std::vector<std::shared_ptr<Floorbot>> linked_floorbots;
};

#endif
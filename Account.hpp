#ifndef ACCOUNT
#define ACCOUNT

class Account {
public:
    Account() = default;
    
    Account(
        std::string username,
        bool is_admin,
        std::vector<Floorbot> linked_floorbots
    ): 
        username(username),
        is_admin(is_admin),
        linked_floorbots(linked_floorbots)
    {}

    std::string username;
    bool is_admin;
    std::vector<Floorbot> linked_floorbots;
};

#endif
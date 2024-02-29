#include "Floorbot.hpp"
#include "Account.hpp"
#include "CommandHandler.hpp"
// #include "DummyObjects.hpp"



int main() {
    CommandHandler handler;

    Floorbot floorbot = Floorbot(
        "Floorbot Mini Shop Demo 1",
        "Floorbot Mini",
        "R7L3X9Y2M6N1",
        "Z300"
    );
    Floorbot::MoveFlag flag = Floorbot::MoveFlag::forward;
    int distance = 5;

    handler.handle_move(floorbot, flag, distance);
    handler.handle_move(floorbot, flag, distance);
    handler.handle_move(floorbot, flag, distance);

    return 0;
}
#include <chrono>
#include <thread>
#include <string>
#include "CTurtle.hpp"

using namespace std;

namespace ct = cturtle;

int main(int argc, char** argv) {
    string command;
    int value;

    string device_id;
    cout << "Please enter your device ID or type 'EXIT' to exit CLI: ";
    cin >> command;
    if (command == "EXIT") {
        cout << "THIS";
        exit(1);
    } else {
        device_id = command;
    }

    string state;
    cout << "Please select a mode from D(iagnostics), C(ontrol), M(odification), or S(oftware Install): ";
    cin >> command;


    ct::TurtleScreen scr;
    ct::Turtle turtle(scr);
    turtle.speed(ct::TS_SLOWEST);

    while (true) {
        cout << "Please enter a command from L(eft), R(ight), F(orward), B(ack): ";
        cin >> command;
        cout << "Please enter a distance or angle: ";
        cin >> value;
        if (command == "Left") {
            turtle.left(value);
            break;
        } else if (command == "Left") {
                turtle.left(value);
                break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    scr.bye();
    return 0;
}

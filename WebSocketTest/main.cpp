#include <iostream>
#include "NetworkController.h"

int main(int args, char **argv) {
    std::string host = "localhost";
    uint port = 8080;
    std::string uri = "/socket/droneSocket";

    NetworkController controller(host, port, uri);
    controller.init();
    controller.startListening();
}
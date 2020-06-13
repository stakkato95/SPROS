//
// Created by artsiom on 13.06.20.
//

#include "NetworkController.h"

using namespace std;

void NetworkController::init(std::string& host, uint port, std::string& uri) {
    droneNetwork = new DroneNetwork(host, port, uri, *this);
    droneNetwork->init();
}

void NetworkController::startListening() {
    listening = true;

    while (listening) {
        try {
            droneNetwork->startListening();
        } catch (exception &e) {
            cout << "Exception " << e.what() << endl;
        }
    }
}

void NetworkController::stopListening() {
    listening = false;
    droneNetwork->stopListening();
}

void NetworkController::onShowUpReceived(const DroneInfo &model) {
    cout << "onShowUpReceived " << model.ip << endl;
}

void NetworkController::onRegistrationReceived(const Registration &model) {
    cout << "onRegistrationReceived " << model.id << endl;
}

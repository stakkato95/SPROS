//
// Created by artsiom on 13.06.20.
//

#include "NetworkController.h"

using namespace std;

NetworkController::NetworkController(string& host, uint port, string& uri) {
    droneNetwork = new DroneNetwork(host, port, uri, *this);
}

void NetworkController::init() {
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
    droneNetwork->getSocket().disconnect();
}

void NetworkController::onShowUpReceived(const DroneInfo &model) {
    cout << "onShowUpReceived " << model.ip << endl;
}

void NetworkController::onRegistrationReceived(const Registration &model) {
    cout << "onRegistrationReceived " << model.id << endl;
    registrationId = model.id;
}

void NetworkController::onStartSessionReceived(const StartSession &model) {
    cout << "onStartSessionReceived " << model.sessionId << endl;
    sessionId = model.sessionId;

    StartSessionAck ack;
    ack.successful = true;
    droneNetwork->getSocket().sendMessage(MESSAGE_TYPE_START_SESSION_ACK, ack);
}

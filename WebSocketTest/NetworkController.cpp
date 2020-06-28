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
            droneNetwork->reconnect();
        }
    }
}

void NetworkController::stopListening() {
    listening = false;
    droneNetwork->getSocket().disconnect();
}

void NetworkController::onConnectedToServer() {
    string tempId = read("tempId.txt");
    string droneId = read("droneId.txt");

    if (tempId.empty() && droneId.empty()) {
        ShowUp showUp;
        showUp.ip = getLocalIpAddress();
        showUp.position = getPosition();
        droneNetwork->getSocket().sendMessage<ShowUp>(MESSAGE_TYPE_SHOW_UP, showUp);
        return;
    }

    if (!tempId.empty()) {
        //send MESSAGE_TYPE_SHOW_UP_TEMP -> send state on server to "unregistered drone is online"
    }

    if (!droneId.empty()) {
        //send MESSAGE_TYPE_SHOW_UP_REGISTERED -> send state on server to "registered drone is online"
    }
}

void NetworkController::onShowUpAckReceived(const ShowUpAck &model) {
    cout << "onShowUpAckReceived " << model.tempId << endl;
    save(model.tempId, "tempId.txt");
}

void NetworkController::onRegistrationReceived(const Registration &model) {
    cout << "onRegistrationReceived " << model.id << endl;
    registrationId = model.id;

    save(registrationId, "droneId.txt");
}

void NetworkController::onStartSessionReceived(const StartSession &model) {
    cout << "onStartSessionReceived " << model.sessionId << endl;
    sessionId = model.sessionId;

    StartSessionAck ack;
    ack.successful = true;
    droneNetwork->getSocket().sendMessage(MESSAGE_TYPE_START_SESSION_ACK, ack);
}

void NetworkController::onPingReceived(const Ping &model) {
    cout << "onPingReceived " << model.timestamp << endl;

    if (registrationId.empty()) {
        registrationId = read("droneId.txt");
    }

    PingAck ack;
    ack.timestamp = getCurrentTimeMillisec();
    //TODO id of a registered drone. currently must be updated mnually.
    //TODO in future should be stored in an SQLite database
    ack.droneId = registrationId;
    droneNetwork->getSocket().sendMessage(MESSAGE_TYPE_PING_ACK, ack);
}

void NetworkController::onStartActionReceived(const StartAction &model) {
    cout << "onStartActionReceived " << model.actionId << endl;

    this_thread::sleep_for(3s);

    ActionFinished actionFinished;
    actionFinished.actionId = model.actionId;
    droneNetwork->getSocket().sendMessage(MESSAGE_TYPE_ACTION_FINISHED, actionFinished);
}

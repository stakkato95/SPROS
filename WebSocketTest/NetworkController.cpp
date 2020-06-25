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

void NetworkController::onShowUpReceived(const DroneInfo &model) {
    cout << "onShowUpReceived " << model.ip << endl;
}

void NetworkController::onRegistrationReceived(const Registration &model) {
    cout << "onRegistrationReceived " << model.id << endl;
    registrationId = model.id;

    //const string path = experimental::filesystem::current_path().string();
    const string path = "/home/artsiom/Documents/repository/SPROS/WebSocketTest/droneId.txt";
    ofstream os(path);
    os << registrationId;
    os.close();
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
        //const string path = experimental::filesystem::current_path().string();
        const string path = "/home/artsiom/Documents/repository/SPROS/WebSocketTest/droneId.txt";
        ifstream is(path);
        is >> registrationId;
        is.close();
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

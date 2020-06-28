//
// Created by artsiom on 13.06.20.
//

#include "DroneNetwork.h"

using namespace std;

using Poco::JSON::Object;

DroneNetwork::DroneNetwork(string &host, uint port, string &uri, NetworkResponder &callback)
        : host{host}, port{port}, uri{uri}, responder{callback} {}

void DroneNetwork::init() {
    factory.registerAdapter(new DroneInfoAdapter(), MESSAGE_TYPE_SHOW_UP);
    factory.registerAdapter(new RegistrationAdapter(), MESSAGE_TYPE_REGISTRATION);
    factory.registerAdapter(new StartSessionAdapter(), MESSAGE_TYPE_START_SESSION);
    factory.registerAdapter(new PingAdapter(), MESSAGE_TYPE_PING);
    factory.registerAdapter(new StartActionAdapter(), MESSAGE_TYPE_START_ACTION);
    factory.registerAdapter(new ShowUpAckAdapter(), MESSAGE_TYPE_SHOW_UP_ACK);
    factory.registerAdapter(new StopSessionAdapter(), MESSAGE_TYPE_STOP_SESSION);

    reconnect();
}

void DroneNetwork::reconnect() {
    socket = new SocketWrapper(host, port, uri);
    socket->connect();

    int attemptToConnect = 1;
    while (!socket->isConnected()) {
        this_thread::sleep_for(2s);
        cout << ++attemptToConnect << " attempt to connect" << endl;
        socket->connect();
    }

    responder.onConnectedToServer();
}

void DroneNetwork::startListening() {
    socket->startListening([&](std::string &messageType, Object::Ptr &objPtr) {
        if (messageType == MESSAGE_TYPE_SHOW_UP_ACK) {
            auto d = factory.parseJson<ShowUpAck>(objPtr, MESSAGE_TYPE_SHOW_UP_ACK);
            responder.onShowUpAckReceived(d);
        } else if (messageType == MESSAGE_TYPE_REGISTRATION) {
            auto r = factory.parseJson<Registration>(objPtr, MESSAGE_TYPE_REGISTRATION);
            responder.onRegistrationReceived(r);
        } else if (messageType == MESSAGE_TYPE_START_SESSION) {
            auto r = factory.parseJson<StartSession>(objPtr, MESSAGE_TYPE_START_SESSION);
            responder.onStartSessionReceived(r);
        } else if (messageType == MESSAGE_TYPE_PING) {
            auto r = factory.parseJson<Ping>(objPtr, MESSAGE_TYPE_PING);
            responder.onPingReceived(r);
        } else if (messageType == MESSAGE_TYPE_START_ACTION) {
            auto r = factory.parseJson<StartAction>(objPtr, MESSAGE_TYPE_START_ACTION);
            responder.onStartActionReceived(r);
        } else if (messageType == MESSAGE_TYPE_STOP_SESSION) {
            auto r = factory.parseJson<StopSession>(objPtr, MESSAGE_TYPE_STOP_SESSION);
            responder.onStopSessionReceived(r);
        }
    });
}

SocketWrapper& DroneNetwork::getSocket() {
    return *socket;
}

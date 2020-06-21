//
// Created by artsiom on 13.06.20.
//

#include "DroneNetwork.h"

using namespace std;

using Poco::JSON::Object;

DroneNetwork::DroneNetwork(string &host, uint port, string &uri, NetCallback &callback)
        : host{host}, port{port}, uri{uri}, callback{callback} {}

void DroneNetwork::init() {
    factory.registerAdapter(new DroneInfoAdapter(), MESSAGE_TYPE_SHOW_UP);
    factory.registerAdapter(new RegistrationAdapter(), MESSAGE_TYPE_REGISTRATION);
    factory.registerAdapter(new StartSessionAdapter(), MESSAGE_TYPE_START_SESSION);
    factory.registerAdapter(new PingAdapter(), MESSAGE_TYPE_PING);
    factory.registerAdapter(new StartActionAdapter(), MESSAGE_TYPE_START_ACTION);

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

    DroneInfo droneInfo;
    droneInfo.ip = getLocalIpAddress();
    droneInfo.position = getPosition();
    socket->sendMessage<DroneInfo>(MESSAGE_TYPE_SHOW_UP, droneInfo);
}

void DroneNetwork::startListening() {
    socket->startListening([&](std::string &messageType, Object::Ptr &objPtr) {
        if (messageType == MESSAGE_TYPE_SHOW_UP) {
            auto d = factory.parseJson<DroneInfo>(objPtr, MESSAGE_TYPE_SHOW_UP);
            callback.onShowUpReceived(d);
        } else if (messageType == MESSAGE_TYPE_REGISTRATION) {
            auto r = factory.parseJson<Registration>(objPtr, MESSAGE_TYPE_REGISTRATION);
            callback.onRegistrationReceived(r);
        } else if (messageType == MESSAGE_TYPE_START_SESSION) {
            auto r = factory.parseJson<StartSession>(objPtr, MESSAGE_TYPE_START_SESSION);
            callback.onStartSessionReceived(r);
        } else if (messageType == MESSAGE_TYPE_PING) {
            auto r = factory.parseJson<Ping>(objPtr, MESSAGE_TYPE_PING);
            callback.onPingReceived(r);
        } else if (messageType == MESSAGE_TYPE_START_ACTION) {
            auto r = factory.parseJson<StartAction>(objPtr, MESSAGE_TYPE_START_ACTION);
            callback.onStartActionReceived(r);
        }
    });
}

SocketWrapper& DroneNetwork::getSocket() {
    return *socket;
}

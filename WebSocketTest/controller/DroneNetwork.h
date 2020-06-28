//
// Created by artsiom on 13.06.20.
//

#ifndef WEBSOCKETTEST_DRONENETWORK_H
#define WEBSOCKETTEST_DRONENETWORK_H

#include <string>
#include <thread>

#include "NetCallback.h"
#include "../net/SocketWrapper.h"

#include "../net/adapter/MessageFactory.h"
#include "../net/adapter/DroneInfoAdapter.h"
#include "../net/adapter/RegistrationAdapter.h"
#include "../net/adapter/StartSessionAdapter.h"
#include "../net/adapter/PingAdapter.h"
#include "../net/adapter/StartActionAdapter.h"
#include "../net/adapter/ShowUpAckAdapter.h"

class DroneNetwork {
public:
    DroneNetwork(std::string& host, uint port, std::string& uri, NetCallback&);

    void init();

    void reconnect();

    void startListening();

    SocketWrapper& getSocket();
private:
    std::string& host;
    uint port;
    std::string& uri;

    bool listening;

    SocketWrapper* socket;
    NetCallback& callback;
    MessageFactory factory;
};


#endif //WEBSOCKETTEST_DRONENETWORK_H

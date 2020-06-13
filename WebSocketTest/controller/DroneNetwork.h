//
// Created by artsiom on 13.06.20.
//

#ifndef WEBSOCKETTEST_DRONENETWORK_H
#define WEBSOCKETTEST_DRONENETWORK_H

#include <string>

#include "NetCallback.h"
#include "../net/SocketWrapper.h"

#include "../net/message/MessageFactory.h"
#include "../net/message/DroneInfoAdapter.h"
#include "../net/message/RegistrationAdapter.h"

class DroneNetwork {
public:
    DroneNetwork(std::string& host, uint port, std::string& uri, NetCallback&);

    void init();

    void startListening();

    void stopListening();

    bool isListening();
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

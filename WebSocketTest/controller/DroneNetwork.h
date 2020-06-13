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

class DroneNetwork : public NetCallback {
public:
    DroneNetwork(std::string& host, uint port, std::string& uri, NetCallback&);

    void init();

    void startListening();
private:
    std::string& host;
    uint port;
    std::string& uri;

    SocketWrapper* socket;
    NetCallback& callback;
    MessageFactory factory;
};


#endif //WEBSOCKETTEST_DRONENETWORK_H

//
// Created by artsiom on 13.06.20.
//

#ifndef WEBSOCKETTEST_NETWORKCONTROLLER_H
#define WEBSOCKETTEST_NETWORKCONTROLLER_H

#include <iostream>

#include "controller/NetCallback.h"
#include "controller/DroneNetwork.h"

class NetworkController : public NetCallback {
public:
    void init(std::string& host, uint port, std::string& uri);

    void startListening();

    void stopListening();

    void onShowUpReceived(const DroneInfo &) override;

    void onRegistrationReceived(const Registration &) override;
private:
    DroneNetwork* droneNetwork;

    bool listening;
};


#endif //WEBSOCKETTEST_NETWORKCONTROLLER_H

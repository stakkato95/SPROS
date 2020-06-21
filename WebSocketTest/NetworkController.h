//
// Created by artsiom on 13.06.20.
//

#ifndef WEBSOCKETTEST_NETWORKCONTROLLER_H
#define WEBSOCKETTEST_NETWORKCONTROLLER_H

#include <iostream>

#include "controller/NetCallback.h"
#include "controller/DroneNetwork.h"

#include "model/acknowledgement/StartSessionAck.h"
#include "model/acknowledgement/PingAck.h"

#include "helper/Helper.h"

class NetworkController : public NetCallback {
public:
    NetworkController(std::string& host, uint port, std::string& uri);

    void init();

    void startListening();

    void stopListening();

    void onShowUpReceived(const DroneInfo &model) override;

    void onRegistrationReceived(const Registration &model) override;

    void onStartSessionReceived(const StartSession &model) override;

    void onPingReceived(const Ping &model) override;
private:
    DroneNetwork* droneNetwork;
    bool listening = false;

    std::string registrationId;
    std::string sessionId;
};


#endif //WEBSOCKETTEST_NETWORKCONTROLLER_H

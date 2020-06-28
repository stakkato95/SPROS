//
// Created by artsiom on 13.06.20.
//

#ifndef WEBSOCKETTEST_NETWORKCONTROLLER_H
#define WEBSOCKETTEST_NETWORKCONTROLLER_H

#include <iostream>
#include <thread>
#include <experimental/filesystem>
#include <iostream>

#include "controller/NetworkResponder.h"
#include "controller/DroneNetwork.h"

#include "model/acknowledgement/StartSessionAck.h"
#include "model/acknowledgement/PingAck.h"
#include "model/acknowledgement/ActionFinished.h"

#include "helper/Helper.h"

class NetworkController : public NetworkResponder {
public:
    NetworkController(std::string& host, uint port, std::string& uri);

    void init();

    void startListening();

    void stopListening();

    void onShowUpAckReceived(const ShowUpAck &model) override;

    void onRegistrationReceived(const Registration &model) override;

    void onStartSessionReceived(const StartSession &model) override;

    void onPingReceived(const Ping &model) override;

    void onStartActionReceived(const StartAction &model) override;
private:
    DroneNetwork* droneNetwork;
    bool listening = false;

    std::string registrationId;
    std::string sessionId;
};


#endif //WEBSOCKETTEST_NETWORKCONTROLLER_H

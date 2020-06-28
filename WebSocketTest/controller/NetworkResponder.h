//
// Created by artsiom on 13.06.20.
//

#ifndef WEBSOCKETTEST_NETWORKRESPONDER_H
#define WEBSOCKETTEST_NETWORKRESPONDER_H

#include "../model/ShowUpAck.h"
#include "../model/Registration.h"
#include "../model/StartSession.h"
#include "../model/Ping.h"
#include "../model/StartAction.h"

class NetworkResponder {
public:
    virtual void onShowUpAckReceived(const ShowUpAck &model) = 0;

    virtual void onRegistrationReceived(const Registration &model) = 0;

    virtual void onStartSessionReceived(const StartSession &model) = 0;

    virtual void onPingReceived(const Ping &model) = 0;

    virtual void onStartActionReceived(const StartAction &model) = 0;
};


#endif //WEBSOCKETTEST_NETWORKRESPONDER_H

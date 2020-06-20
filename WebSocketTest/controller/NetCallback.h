//
// Created by artsiom on 13.06.20.
//

#ifndef WEBSOCKETTEST_NETCALLBACK_H
#define WEBSOCKETTEST_NETCALLBACK_H

#include "../model/DroneInfo.h"
#include "../model/Registration.h"
#include "../model/StartSession.h"

class NetCallback {
public:
    virtual void onShowUpReceived(const DroneInfo &model) = 0;

    virtual void onRegistrationReceived(const Registration &model) = 0;

    virtual void onStartSessionReceived(const StartSession &model) = 0;
};


#endif //WEBSOCKETTEST_NETCALLBACK_H

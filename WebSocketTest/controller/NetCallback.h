//
// Created by artsiom on 13.06.20.
//

#ifndef WEBSOCKETTEST_NETCALLBACK_H
#define WEBSOCKETTEST_NETCALLBACK_H

#include "../model/DroneInfo.h"
#include "../model/Registration.h"

class NetCallback {
public:
    virtual void onShowUpReceived(const DroneInfo &) = 0;

    virtual void onRegistrationReceived(const Registration &) = 0;
};


#endif //WEBSOCKETTEST_NETCALLBACK_H

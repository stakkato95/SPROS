//
// Created by artsiom on 13.06.20.
//

#ifndef WEBSOCKETTEST_DRONEINFOADAPTER_H
#define WEBSOCKETTEST_DRONEINFOADAPTER_H

#include "MessageAdapter.h"
#include "../../model/request/ShowUp.h"

class DroneInfoAdapter : public MessageAdapter<ShowUp> {
public:
    ShowUp getModel(Poco::JSON::Object::Ptr& objPtr) const noexcept(false) override {
        using Poco::JSON::Object;
        using namespace std;

        ShowUp info;
        info.ip = objPtr->getValue<string>("ip");

        Object::Ptr posPtr = objPtr->getObject("position");
        info.position = Position();
        info.position.lat = posPtr->getValue<float>("lat");
        info.position.lon = posPtr->getValue<float>("lon");
        info.position.alt = posPtr->getValue<float>("alt");

        return info;
    }
};

#endif //WEBSOCKETTEST_DRONEINFOADAPTER_H

//
// Created by artsiom on 13.06.20.
//

#ifndef WEBSOCKETTEST_STARTACTIONADAPTER_H
#define WEBSOCKETTEST_STARTACTIONADAPTER_H

#include "MessageAdapter.h"
#include "../../model/StartAction.h"

class StartActionAdapter : public MessageAdapter<StartAction> {
public:
    StartAction getModel(Poco::JSON::Object::Ptr& objPtr) const noexcept(false) override {
        using Poco::JSON::Object;
        using namespace std;

        StartAction info;
        info.actionId = objPtr->getValue<string>("actionId");
        info.actionType = objPtr->getValue<string>("actionType");
        info.value = objPtr->getValue<float>("value");

        return info;
    }
};

#endif //WEBSOCKETTEST_STARTACTIONADAPTER_H

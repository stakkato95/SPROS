//
// Created by artsiom on 21.06.20.
//

#ifndef WEBSOCKETTEST_PINGADAPTER_H
#define WEBSOCKETTEST_PINGADAPTER_H

#include "MessageAdapter.h"
#include "../../model/receivedFromServer/Ping.h"

class PingAdapter : public MessageAdapter<Ping> {
public:
    Ping getModel(Poco::JSON::Object::Ptr& objPtr) const noexcept(false) override {
        using Poco::JSON::Object;
        using namespace std;

        Ping info;
        info.timestamp = objPtr->getValue<string>("timestamp");

        return info;
    }
};

#endif //WEBSOCKETTEST_PINGADAPTER_H

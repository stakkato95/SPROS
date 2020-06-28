//
// Created by artsiom on 13.06.20.
//

#ifndef WEBSOCKETTEST_STARTSESSIONADAPTER_H
#define WEBSOCKETTEST_STARTSESSIONADAPTER_H

#include "MessageAdapter.h"
#include "../../model/receivedFromServer/StartSession.h"

class StartSessionAdapter : public MessageAdapter<StartSession> {
public:
    StartSession getModel(Poco::JSON::Object::Ptr& objPtr) const noexcept(false) override {
        using Poco::JSON::Object;
        using namespace std;

        StartSession info;
        info.sessionId = objPtr->getValue<string>("sessionId");

        return info;
    }
};

#endif //WEBSOCKETTEST_STARTSESSIONADAPTER_H

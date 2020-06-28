//
// Created by artsiom on 28.06.20.
//

#ifndef WEBSOCKETTEST_STOPSESSIONADAPTER_H
#define WEBSOCKETTEST_STOPSESSIONADAPTER_H

#include "MessageAdapter.h"
#include "../../model/receivedFromServer/StopSession.h"

class StopSessionAdapter : public MessageAdapter<StopSession> {
public:
    StopSession getModel(Poco::JSON::Object::Ptr& objPtr) const noexcept(false) override {
        using Poco::JSON::Object;
        using namespace std;

        StopSession stopSession;
        stopSession.sessionId = objPtr->getValue<string>("sessionId");

        return stopSession;
    }
};

#endif //WEBSOCKETTEST_STOPSESSIONADAPTER_H

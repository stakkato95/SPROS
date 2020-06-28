//
// Created by artsiom on 28.06.20.
//

#ifndef WEBSOCKETTEST_SHOWUPACKADAPTER_H
#define WEBSOCKETTEST_SHOWUPACKADAPTER_H

#include "MessageAdapter.h"
#include "../../model/response/ShowUpAck.h"

class ShowUpAckAdapter : public MessageAdapter<ShowUpAck> {
public:
    ShowUpAck getModel(Poco::JSON::Object::Ptr& objPtr) const noexcept(false) override {
        return { objPtr->getValue<std::string>("tempId") };
    }
};

#endif //WEBSOCKETTEST_SHOWUPACKADAPTER_H

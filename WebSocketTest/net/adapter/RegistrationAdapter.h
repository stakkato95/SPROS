//
// Created by artsiom on 13.06.20.
//

#ifndef WEBSOCKETTEST_REGISTRATIONADAPTER_H
#define WEBSOCKETTEST_REGISTRATIONADAPTER_H

#include "MessageAdapter.h"
#include "../../model/receivedFromServer/Registration.h"

class RegistrationAdapter : public MessageAdapter<Registration> {
public:
    Registration getModel(Poco::JSON::Object::Ptr& objPtr) const noexcept(false) override {
        return { objPtr->getValue<std::string>("id") };
    }
};

#endif //WEBSOCKETTEST_REGISTRATIONADAPTER_H

//
// Created by artsiom on 13.06.20.
//

#ifndef WEBSOCKETTEST_REGISTRATIONADAPTER_H
#define WEBSOCKETTEST_REGISTRATIONADAPTER_H

#include "MessageAdapter.h"
#include "../../model/Registration.h"

class RegistrationAdapter : public MessageAdapter<Registration> {
public:
    Registration getModel(Poco::JSON::Object::Ptr&) const noexcept(false) override;
};


#endif //WEBSOCKETTEST_REGISTRATIONADAPTER_H

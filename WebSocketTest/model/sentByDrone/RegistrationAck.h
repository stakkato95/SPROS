//
// Created by artsiom on 28.06.20.
//

#ifndef WEBSOCKETTEST_REGISTRATIONACK_H
#define WEBSOCKETTEST_REGISTRATIONACK_H

#include "Model.h"
#include <string>

struct RegistrationAck : public Model {
    std::string droneId;

    boost::property_tree::ptree getTree() const override {
        boost::property_tree::ptree out;

        out.put("droneId", this->droneId);

        return out;
    }
};

#endif //WEBSOCKETTEST_REGISTRATIONACK_H

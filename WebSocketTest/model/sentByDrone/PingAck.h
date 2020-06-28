//
// Created by artsiom on 21.06.20.
//

#ifndef WEBSOCKETTEST_PINGACK_H
#define WEBSOCKETTEST_PINGACK_H

#include <string>

#include "Model.h"

struct PingAck : public Model {
    long long timestamp;
    std::string droneId;

    boost::property_tree::ptree getTree() const override {
        boost::property_tree::ptree out;

        out.put("timestamp", this->timestamp);
        out.put("droneId", this->droneId);

        return out;
    }
};

#endif //WEBSOCKETTEST_PINGACK_H

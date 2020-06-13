//
// Created by artsiom on 13.06.20.
//

#ifndef WEBSOCKETTEST_DRONEINFO_H
#define WEBSOCKETTEST_DRONEINFO_H

#include <string>

#include "Model.h"
#include "Position.h"

struct DroneInfo : public Model {
    std::string ip;
    Position position;

    boost::property_tree::ptree getTree() const override {
        boost::property_tree::ptree out;

        out.put("ip", this->ip);
        out.put_child("position", this->position.getTree());

        return out;
    }
};

#endif //WEBSOCKETTEST_DRONEINFO_H

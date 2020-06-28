//
// Created by artsiom on 28.06.20.
//

#ifndef WEBSOCKETTEST_STOPSESSIONACK_H
#define WEBSOCKETTEST_STOPSESSIONACK_H

#include "Model.h"

struct StopSessionAck : public Model {
    std::string sessionId;

    boost::property_tree::ptree getTree() const override {
        boost::property_tree::ptree out;

        out.put("sessionId", this->sessionId);

        return out;
    }
};

#endif //WEBSOCKETTEST_STOPSESSIONACK_H

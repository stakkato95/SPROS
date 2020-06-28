//
// Created by artsiom on 20.06.20.
//

#ifndef WEBSOCKETTEST_STARTSESSIONACK_H
#define WEBSOCKETTEST_STARTSESSIONACK_H

#include "Model.h"

struct StartSessionAck : public Model {
    std::string sessionId;

    boost::property_tree::ptree getTree() const override {
        boost::property_tree::ptree out;

        out.put("sessionId", this->sessionId);

        return out;
    }
};

#endif //WEBSOCKETTEST_STARTSESSIONACK_H

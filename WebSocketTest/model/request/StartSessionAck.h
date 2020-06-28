//
// Created by artsiom on 20.06.20.
//

#ifndef WEBSOCKETTEST_STARTSESSIONACK_H
#define WEBSOCKETTEST_STARTSESSIONACK_H

#include "Model.h"

struct StartSessionAck : public Model {
    bool successful;

    boost::property_tree::ptree getTree() const override {
        boost::property_tree::ptree out;

        out.put("successful", this->successful);

        return out;
    }
};

#endif //WEBSOCKETTEST_STARTSESSIONACK_H

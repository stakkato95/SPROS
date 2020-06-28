//
// Created by artsiom on 21.06.20.
//

#ifndef WEBSOCKETTEST_ACTIONFINISHED_H
#define WEBSOCKETTEST_ACTIONFINISHED_H

#include <string>

#include "Model.h"

struct ActionFinished : public Model {
    std::string actionId;

    boost::property_tree::ptree getTree() const override {
        boost::property_tree::ptree out;

        out.put("actionId", this->actionId);

        return out;
    }
};

#endif //WEBSOCKETTEST_ACTIONFINISHED_H

//
// Created by artsiom on 13.06.20.
//

#ifndef WEBSOCKETTEST_POSITION_H
#define WEBSOCKETTEST_POSITION_H

#include "Model.h"

struct Position : public Model {
    float lat;
    float lon;
    float alt;

    boost::property_tree::ptree getTree() const override;
};

#endif //WEBSOCKETTEST_POSITION_H

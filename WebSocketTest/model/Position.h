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

    boost::property_tree::ptree getTree() const override {
        boost::property_tree::ptree out;

        out.put("lat", this->lat);
        out.put("lon", this->lon);
        out.put("alt", this->alt);

        return out;
    }
};

#endif //WEBSOCKETTEST_POSITION_H

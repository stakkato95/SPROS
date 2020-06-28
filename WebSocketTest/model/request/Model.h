//
// Created by artsiom on 13.06.20.
//

#ifndef WEBSOCKETTEST_MODEL_H
#define WEBSOCKETTEST_MODEL_H

#include <boost/property_tree/ptree.hpp>

struct Model {
    virtual boost::property_tree::ptree getTree() const = 0;
};

#endif //WEBSOCKETTEST_MODEL_H

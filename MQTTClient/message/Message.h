//
// Created by artsiom on 26.06.20.
//

#ifndef MQTTCLIENT_MESSAGE_H
#define MQTTCLIENT_MESSAGE_H

#include <boost/property_tree/ptree.hpp>

struct Message {
    virtual boost::property_tree::ptree getTree() const = 0;
};

#endif //MQTTCLIENT_MESSAGE_H

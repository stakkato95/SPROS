//
// Created by artsiom on 26.06.20.
//

#ifndef MQTTCLIENT_GNSSMESSAGE_H
#define MQTTCLIENT_GNSSMESSAGE_H

#include "Message.h"

struct GNSSMessage : public Message {
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

#endif //MQTTCLIENT_GNSSMESSAGE_H

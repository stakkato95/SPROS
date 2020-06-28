//
// Created by artsiom on 27.06.20.
//

#ifndef MQTTCLIENT_SPEEDMESSAGE_H
#define MQTTCLIENT_SPEEDMESSAGE_H

#include "Message.h"

struct SpeedMessage : public Message {
    float x;
    float y;
    float z;

    boost::property_tree::ptree getTree() const override {
        boost::property_tree::ptree out;

        out.put("timestamp", this->timestamp);
        out.put("x", this->x);
        out.put("y", this->y);
        out.put("z", this->z);

        return out;
    }
};

#endif //MQTTCLIENT_SPEEDMESSAGE_H

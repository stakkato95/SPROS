//
// Created by artsiom on 27.06.20.
//

#ifndef MQTTCLIENT_ROTATIONMESSAGE_H
#define MQTTCLIENT_ROTATIONMESSAGE_H

#include "Message.h"

struct RotationMessage : public Message {
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

#endif //MQTTCLIENT_ROTATIONMESSAGE_H

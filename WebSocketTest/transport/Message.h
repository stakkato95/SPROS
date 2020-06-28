//
// Created by artsiom on 13.06.20.
//

#ifndef WEBSOCKETTEST_MESSAGE_H
#define WEBSOCKETTEST_MESSAGE_H

#include <string>

#include "../model/request/Model.h"

template<typename T>
struct Message : public Model {
    std::string messageType;
    T payload;

    boost::property_tree::ptree getTree() const override {
        boost::property_tree::ptree out;

        out.put("messageType", this->messageType);
        out.put_child("payload", this->payload.getTree());

        return out;
    }
};


#endif //WEBSOCKETTEST_MESSAGE_H

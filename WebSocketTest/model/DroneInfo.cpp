//
// Created by artsiom on 13.06.20.
//

#include "DroneInfo.h"
#include "../helper/Helper.h"

using boost::property_tree::ptree;

ptree DroneInfo::getTree() const {
    ptree out;

    out.put("ip", this->ip);
    out.put_child("position", this->position.getTree());

    return out;
}

//
// Created by artsiom on 13.06.20.
//

#include "Position.h"

using boost::property_tree::ptree;

ptree Position::getTree() const {
    ptree out;

    out.put("lat", this->lat);
    out.put("lon", this->lon);
    out.put("alt", this->alt);

    return out;
}


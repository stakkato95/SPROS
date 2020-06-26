//
// Created by artsiom on 26.06.20.
//

#ifndef MQTTCLIENT_HELPER_H
#define MQTTCLIENT_HELPER_H

#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using boost::property_tree::ptree;

static std::string treeToString(const ptree& tree) {
    std::ostringstream oss;
    boost::property_tree::write_json(oss, tree);
    return oss.str();
}

#endif //MQTTCLIENT_HELPER_H

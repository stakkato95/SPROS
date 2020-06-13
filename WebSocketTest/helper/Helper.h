//
// Created by artsiom on 13.06.20.
//

#ifndef WEBSOCKETTEST_HELPER_H
#define WEBSOCKETTEST_HELPER_H

#include <iostream>
#include <sstream>

#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using boost::asio::ip::udp;
using boost::property_tree::ptree;

static std::string getLocalIpAddress() {
    try {
        boost::asio::io_service netService;
        udp::resolver resolver(netService);
        udp::resolver::query query(udp::v4(), "google.com", "");
        udp::resolver::iterator endpoints = resolver.resolve(query);
        udp::endpoint ep = *endpoints;
        udp::socket socket(netService);
        socket.connect(ep);
        return socket.local_endpoint().address().to_string();
    } catch (std::exception &e) {
        return "unknown";
    }
}

static Position getPosition() {
    Position p;
    p.lat = 11.11;
    p.lon = 22.22;
    p.alt = 33.33;
    return p;
}

static std::string treeToString(ptree tree) {
    std::ostringstream oss;
    boost::property_tree::write_json(oss, tree);
    return oss.str();
}

#endif //WEBSOCKETTEST_HELPER_H

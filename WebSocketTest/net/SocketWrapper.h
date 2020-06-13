//
// Created by artsiom on 13.06.20.
//

#ifndef WEBSOCKETTEST_SOCKETWRAPPER_H
#define WEBSOCKETTEST_SOCKETWRAPPER_H

#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPMessage.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Net/HTTPClientSession.h"

#include "Poco/JSON/Parser.h"
#include "Poco/JSON/ParseHandler.h"
#include "Poco/JSON/JSONException.h"

#include <iostream>
#include <string>
#include <functional>

#include "../model/DroneInfo.h"
#include "../transport/Message.h"
#include "../Helper.h"
#include "../MessageTypeConst.h"
#include "message/MessageFactory.h"

class SocketWrapper {
public:
    SocketWrapper(std::string&& host, uint port, std::string&& uri);

    void connect() noexcept(false);

    void disconnect() noexcept(false);

    template<typename T>
    void sendMessage(std::string &&type, T data) noexcept(false) {
        Message<T> m;
        m.messageType = type;
        m.payload = data;

        std::string message = treeToString(m.getTree());
        char const *testStr = message.c_str();

        int len = socket->sendFrame(testStr, strlen(testStr), Poco::Net::WebSocket::FRAME_TEXT);
        std::cout << "Sent bytes " << len << std::endl;
    }

    void startListening(std::function<void(std::string &, Poco::JSON::Object::Ptr &)> &) noexcept(false);

private:
    static const int RECEIVE_BUFFER_SIZE = 1024;

    std::string host;
    std::string uri;
    uint port;

    Poco::Net::WebSocket *socket;
    char receiveBuff[RECEIVE_BUFFER_SIZE];
    bool isConnected;

    Poco::JSON::Parser parser;
};


#endif //WEBSOCKETTEST_SOCKETWRAPPER_H

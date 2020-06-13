//
// Created by artsiom on 13.06.20.
//

#include "SocketWrapper.h"

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::Net::WebSocket;

using namespace std;

SocketWrapper::SocketWrapper(string &host, string &uri, uint port) : host{host}, uri{uri}, port{port} {}

void SocketWrapper::connect() {
    HTTPClientSession cs(host, port);
    HTTPRequest request(HTTPRequest::HTTP_GET, uri, HTTPMessage::HTTP_1_1);
    HTTPResponse response;
    socket = new WebSocket(cs, request, response);
}

void SocketWrapper::disconnect() {
    isConnected = false;
    socket->close();
}

void SocketWrapper::startListening() {
    int flags = 0;

    while (isConnected) {
        int frameLength = socket->receiveFrame(receiveBuff, RECEIVE_BUFFER_SIZE, flags);
        std::cout << "Received bytes " << frameLength << std::endl;
        std::cout << receiveBuff << std::endl;

        string data(receiveBuff, 0, frameLength);

    }
}

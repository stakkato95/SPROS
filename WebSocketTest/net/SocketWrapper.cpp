//
// Created by artsiom on 13.06.20.
//

#include "SocketWrapper.h"

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::Net::WebSocket;

using Poco::JSON::Object;

using namespace std;

SocketWrapper::SocketWrapper(string& host, uint port, string& uri) : host{host}, port{port}, uri{uri} {}

void SocketWrapper::connect() {
    HTTPClientSession cs(host, port);
    HTTPRequest request(HTTPRequest::HTTP_GET, uri, HTTPMessage::HTTP_1_1);
    HTTPResponse response;
    socket = new WebSocket(cs, request, response);
    connected = true;
}

void SocketWrapper::disconnect() {
    connected = false;
    socket->close();
}

bool SocketWrapper::isConnected() {
    return connected;
}

void SocketWrapper::startListening(function<void(string&, Object::Ptr &)>&& callback) {
    int flags = 0;

    while (connected) {
        int frameLength = socket->receiveFrame(receiveBuff, RECEIVE_BUFFER_SIZE, flags);
        std::cout << "Received bytes " << frameLength << std::endl;
        std::cout << receiveBuff << std::endl;

        string data(receiveBuff, 0, frameLength);

        Object::Ptr objPtr = parser.parse(data).extract<Object::Ptr>();
        string messageType = objPtr->getValue<string>("messageType");
        Object::Ptr payload = objPtr->getObject("payload");

        callback(messageType, payload);
    }
}

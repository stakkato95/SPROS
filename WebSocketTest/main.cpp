#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPMessage.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Net/HTTPClientSession.h"

#include <iostream>

#include "model/DroneInfo.h"
#include "model/Registration.h"

#include "transport/Message.h"
#include "Helper.h"
#include "net/SocketWrapper.h"
#include "MessageTypeConst.h"

#include "net/message/MessageFactory.h"
#include "net/message/RegistrationAdapter.h"

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::Net::WebSocket;

using Poco::JSON::Object;

int main(int args, char **argv) {
    try {
        MessageFactory factory;
        factory.registerAdapter(new RegistrationAdapter(), MESSAGE_TYPE_REGISTRATION);

        SocketWrapper socket("localhost", 8080, "/socket/droneSocket");
        socket.connect();

        DroneInfo droneInfo;
        droneInfo.ip = getLocalIpAddress();
        droneInfo.position = getPosition();
        socket.sendMessage<DroneInfo>(MESSAGE_TYPE_SHOW_UP, droneInfo);

        socket.startListening([&](std::string& messageType, Object::Ptr &objPtr) {
            std::cout << messageType << std::endl;

            if (messageType == MESSAGE_TYPE_SHOW_UP) {

            } else if (messageType == MESSAGE_TYPE_REGISTRATION) {
                auto r = factory.parseJson<Registration>(objPtr, MESSAGE_TYPE_REGISTRATION);
                std::cout << r.id << std::endl;
            }
        });
    } catch (std::exception &e) {
        std::cout << "Exception " << e.what();
    }


//    HTTPClientSession cs("localhost", 8080);
//    HTTPRequest request(HTTPRequest::HTTP_GET, "/socket/droneSocket", HTTPMessage::HTTP_1_1);
//    HTTPResponse response;
//
//    try {
//        WebSocket *m_psock = new WebSocket(cs, request, response);
//
//        DroneInfo droneInfo;
//        droneInfo.ip = getLocalIpAddress();
//        droneInfo.position = getPosition();
//        Message<DroneInfo> m;
//        m.messageType = "SHOW_UP";
//        m.payload = droneInfo;
//
//        std::string message = treeToString(m.getTree());
//        char const *testStr = message.c_str();
//        char receiveBuff[256];
//
//        int len = m_psock->sendFrame(testStr, strlen(testStr), WebSocket::FRAME_TEXT);
//        std::cout << "Sent bytes " << len << std::endl;
//        int flags = 0;
//
//        int rlen = m_psock->receiveFrame(receiveBuff, 256, flags);
//        std::cout << "Received bytes " << rlen << std::endl;
//        std::cout << receiveBuff << std::endl;
//
//        m_psock->close();
//
//    } catch (std::exception &e) {
//        std::cout << "Exception " << e.what();
//    }
}
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPMessage.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Net/HTTPClientSession.h"

#include <iostream>

#include "model/DroneInfo.h"
#include "model/Registration.h"

#include "transport/Message.h"
#include "helper/Helper.h"
#include "net/SocketWrapper.h"
#include "helper/MessageTypeConst.h"

#include "net/message/MessageFactory.h"
#include "net/message/DroneInfoAdapter.h"
#include "net/message/RegistrationAdapter.h"

#include "NetworkController.h"

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::Net::WebSocket;

using Poco::JSON::Object;

int main(int args, char **argv) {
    std::string host = "localhost";
    uint port = 8080;
    std::string uri = "/socket/droneSocket";

    NetworkController controller;
    controller.init(host, port, uri);
    controller.startListening();
}
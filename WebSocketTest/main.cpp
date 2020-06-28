#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPMessage.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/Net/HTTPClientSession.h"

#include <iostream>

#include "model/request/ShowUp.h"
#include "model/response/Registration.h"

#include "transport/Message.h"
#include "helper/Helper.h"
#include "net/SocketWrapper.h"
#include "helper/MessageTypeConst.h"

#include "net/adapter/MessageFactory.h"
#include "net/adapter/DroneInfoAdapter.h"
#include "net/adapter/RegistrationAdapter.h"

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

    NetworkController controller(host, port, uri);
    controller.init();
    controller.startListening();
}
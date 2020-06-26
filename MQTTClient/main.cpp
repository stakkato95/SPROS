#include <iostream>
#include <string>
#include <cstring>
#include "mqtt/async_client.h"

#include "helper/Helper.h"
#include "message/GNSSMessage.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
    GNSSMessage msg;
    msg.lat = 100;
    msg.lon = 500;
    msg.alt = 100;

    const int QOS = 1;
    boost::property_tree::ptree tree = msg.getTree();
    std::string json = treeToString(tree);
    const char* payload = json.c_str();

    string address = "tcp://localhost:1883";

    cout << "Initializing for server '" << address << "'..." << endl;
    mqtt::async_client cli(address, "");
    cout << "OK" << endl;

    try {
        cout << "\nConnecting..." << endl;
        cli.connect()->wait();
        cout << "OK" << endl;
        cout << "\nPublishing messages..." << endl;

        mqtt::topic top(cli, "drone/telemetry/gnss", QOS);
        mqtt::token_ptr tok;

        tok = top.publish(payload);
        tok->wait();// Just wait for the last one to complete.
        cout << "OK" << endl;

        // Disconnect
        cout << "\nDisconnecting..." << endl;
        cli.disconnect()->wait();
        cout << "OK" << endl;
    }
    catch (const mqtt::exception& exc) {
        cerr << exc.what() << endl;
        return 1;
    }

    return 0;
}
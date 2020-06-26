#include <iostream>
#include <string>
#include <cstring>
#include "mqtt/async_client.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
    const int QOS = 1;
    const char* payload = "my msg";
    string address = "tcp://localhost:1883";

    cout << "Initializing for server '" << address << "'..." << endl;
    mqtt::async_client cli(address, "");

    cout << "  ...OK" << endl;

    try {
        cout << "\nConnecting..." << endl;
        cli.connect()->wait();
        cout << "  ...OK" << endl;

        cout << "\nPublishing messages..." << endl;

        mqtt::topic top(cli, "test", QOS);
        mqtt::token_ptr tok;

        size_t i = 0;
        tok = top.publish(payload);
        tok->wait();	// Just wait for the last one to complete.
        cout << "OK" << endl;

        // Disconnect
        cout << "\nDisconnecting..." << endl;
        cli.disconnect()->wait();
        cout << "  ...OK" << endl;
    }
    catch (const mqtt::exception& exc) {
        cerr << exc.what() << endl;
        return 1;
    }

    return 0;
}
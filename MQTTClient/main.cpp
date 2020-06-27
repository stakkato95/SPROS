#include <iostream>
#include <string>
#include <thread>
#include <random>
#include <chrono>
#include "mqtt/async_client.h"

#include "helper/Helper.h"
#include "message/GNSSMessage.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////

default_random_engine rnd(std::chrono::system_clock::now().time_since_epoch().count());

float getGnssLatLonNoise() {
    static uniform_real_distribution<> distribution { -0.000003, 0.000004 };
    return distribution(rnd);
}

float getGnssAltNoise() {
    static uniform_int_distribution<> distribution { -20, 20 };
    return distribution(rnd);
}

GNSSMessage getNoisyGnssMessage(GNSSMessage msg) {
    msg.lat += getGnssLatLonNoise();
    msg.lon += getGnssLatLonNoise();
    msg.alt += getGnssAltNoise();
    return msg;
}

void sendMessages(mqtt::topic& topicGnss, mqtt::topic& topicSpeed, mqtt::topic& topicRotation) {
    GNSSMessage msg;
    msg.lat = 48.3721216;
    msg.lon = 14.5195008;
    msg.alt = 400;

    mqtt::token_ptr tok;

    while (true) {
        GNSSMessage noisyMsg = getNoisyGnssMessage(msg);
        boost::property_tree::ptree tree = noisyMsg.getTree();
        string json = treeToString(tree);
        const char* payload = json.c_str();
        cout << payload << endl;

        tok = topicGnss.publish(payload);
        tok->wait();// Just wait for the last one to complete.
        cout << "OK" << endl;
        this_thread::sleep_for(1s);
    }
}

int main(int argc, char* argv[])
{
    string address = "tcp://localhost:1883";
    const int QOS_AT_LEAST_ONCE = 1;
    mqtt::async_client cli(address, "");

    try {
        cli.connect()->wait();
        cout << "Connected to server" << endl;

        mqtt::topic topicGnss(cli, "drone/telemetry/gnss", QOS_AT_LEAST_ONCE);
        mqtt::topic topicSpeed(cli, "drone/telemetry/speed", QOS_AT_LEAST_ONCE);
        mqtt::topic topicRotation(cli, "drone/telemetry/rotation", QOS_AT_LEAST_ONCE);

        sendMessages(topicGnss, topicSpeed, topicRotation);

        // Disconnect
        cout << "Disconnecting..." << endl;
        cli.disconnect()->wait();
        cout << "OK" << endl;
    }
    catch (const mqtt::exception& exc) {
        cerr << exc.what() << endl;
        return 1;
    }

    return 0;
}
#include <iostream>
#include <string>
#include <thread>
#include <random>
#include <chrono>
#include "mqtt/async_client.h"

#include "helper/Helper.h"
#include "message/GNSSMessage.h"
#include "message/SpeedMessage.h"
#include "message/RotationMessage.h"

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

float getRotationAndSpeedNoise() {
    static uniform_real_distribution<> distribution { -0.05, 0.05 };
    return distribution(rnd);
}

RotationMessage getNoisyRotationMessage(RotationMessage msg) {
    msg.x += getRotationAndSpeedNoise();
    msg.y += getRotationAndSpeedNoise();
    msg.z += getRotationAndSpeedNoise();
    return msg;
}

SpeedMessage getNoisySpeedMessage(SpeedMessage msg) {
    msg.x += getRotationAndSpeedNoise();
    msg.y += getRotationAndSpeedNoise();
    msg.z += getRotationAndSpeedNoise();
    return msg;
}

void sendMessages(mqtt::topic& topicGnss, mqtt::topic& topicSpeed, mqtt::topic& topicRotation) {
    GNSSMessage msgGnss;
    msgGnss.lat = 48.3721216;
    msgGnss.lon = 14.5195008;
    msgGnss.alt = 400;

    RotationMessage msgRotation;
    msgRotation.x = 0.1;
    msgRotation.y = 0.2;
    msgRotation.z = 0.3;

    SpeedMessage msgSpeed;
    msgSpeed.x = 0.5;
    msgSpeed.y = 0.1;
    msgSpeed.z = 0.5;

    mqtt::token_ptr tok;

    int count = 0;
    while (true) {
        long long timestamp = getCurrentTimeMillisec();

        GNSSMessage msgGnssNoisy = getNoisyGnssMessage(msgGnss);
        msgGnssNoisy.timestamp = timestamp;
        RotationMessage msgRotationNoisy = getNoisyRotationMessage(msgRotation);
        msgRotationNoisy.timestamp = timestamp;
        SpeedMessage msgSpeedNoisy = getNoisySpeedMessage(msgSpeed);
        msgSpeedNoisy.timestamp = timestamp;

        boost::property_tree::ptree tree = msgGnssNoisy.getTree();
        string json = treeToString(tree);
        const char* payload = json.c_str();
        tok = topicGnss.publish(payload);
        tok->wait();

        tree = msgRotationNoisy.getTree();
        json = treeToString(tree);
        payload = json.c_str();
        tok = topicRotation.publish(payload);
        tok->wait();

        tree = msgSpeedNoisy.getTree();
        json = treeToString(tree);
        payload = json.c_str();
        tok = topicSpeed.publish(payload);
        tok->wait();

        cout << "OK " << ++count << endl;
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
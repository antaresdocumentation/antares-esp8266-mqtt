#ifndef ANTARESESP8266MQTT_H
#define ANTARESESP8266MQTT_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

class AntaresESP8266MQTT {

private:
    const char* _mqttServer = "platform.antares.id";
    const int _mqttPort = 1883;
    const int _secureMqttPort = 8883;
    bool _debug;
    char* _wifiSSID;
    char* _wifiPass;
    String _accessKey;

public:
    AntaresESP8266MQTT(String accessKey);
    bool wifiConnection(String SSID, String wifiPassword);
    bool setDebug(bool trueFalse);
    void printDebug(String text);
    String ipToString(IPAddress ip);

    void setMqttServer();
    void checkMqttConnection();
};

#endif

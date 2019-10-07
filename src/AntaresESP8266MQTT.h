#ifndef ANTARESESP8266MQTT_H
#define ANTARESESP8266MQTT_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

class AntaresESP8266MQTT {

private:
    const char* _mqttServer = "mqtt.antares.id";
    const int _mqttPort = 1883;
    const int _secureMqttPort = 8883;
    bool _debug;
    char* _wifiSSID;
    char* _wifiPass;
    String _accessKey;
    String _jsonDataString = "{}";
    String _jsonSubDataString;
    String _subscriptionTopic;
    String _receivedTopic;

public:
    AntaresESP8266MQTT(String accessKey);
    bool wifiConnection(String SSID, String wifiPassword);
    bool setDebug(bool trueFalse);
    void printDebug(String text);
    String ipToString(IPAddress ip);
    /* Overloaded functions: Add data to temporary storage */
    void add(String key, int value);
    void add(String key, float value);
    void add(String key, double value);
    void add(String key, String value);
    /* Overloaded functions end */
    void printData();
    void publish(String projectName, String deviceName);
    /* Get subscription callback data*/
    int getInt(String key);
    float getFloat(String key);
    double getDouble(String key);
    String getString(String key);
    /* Get data end */

    String getTopic();
    String getPayload();

    void setMqttServer();
    void checkMqttConnection();
    void setCallback(std::function<void(char*, uint8_t*, unsigned int)> callbackFunc);
    String get(char* topic, byte* payload, unsigned int length);
    void setSubscriptionTopic();
};

#endif

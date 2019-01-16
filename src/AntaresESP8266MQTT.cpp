#include "AntaresESP8266MQTT.h"

WiFiClient espClient;
PubSubClient client(espClient);

AntaresESP8266MQTT::AntaresESP8266MQTT(String accessKey) {
    _accessKey = accessKey;
}

void AntaresESP8266MQTT::setMqttServer() {
    if(WiFi.status() != WL_CONNECTED) {
        printDebug("[ANTARES] Unable to connect to MQTT server.\n");
    }
    else {
        printDebug("[ANTARES] Setting MQTT server \"" + String(_mqttServer) + "\" on port " + String(_mqttPort) + "\n");
        client.setServer(_mqttServer, _mqttPort);
    }

}

void AntaresESP8266MQTT::checkMqttConnection() {
    if(!client.connected()) {
        while(!client.connected()) {
            printDebug("[ANTARES] Attempting MQTT connection...\n");
            if(client.connect("ESP8266-TESTVALIAN")) {
                printDebug("[ANTARES] Connected!");
                client.publish("testvalian", "connect!");
            }
            else {
                printDebug("[ANTARES] Failed, rc=" + String(client.state()) + ", Will try again in 5 secs.\n");
                delay(5000);
            }
        }
    }
    client.loop();
}

bool AntaresESP8266MQTT::wifiConnection(String SSID, String wifiPassword) {
    char ssidChar[sizeof(SSID)];
    char wifiPasswordChar[sizeof(wifiPassword)];

    SSID.toCharArray(ssidChar, sizeof(SSID));
    wifiPassword.toCharArray(wifiPasswordChar, sizeof(wifiPassword));

    int count = 0;
    _wifiSSID = ssidChar;
    _wifiPass = wifiPasswordChar;

    WiFi.begin(_wifiSSID, _wifiPass);
    printDebug("[ANTARES] Trying to connect to " + SSID + "...\n");

    for (count=0;count<20;count++)
    {
      delay(500);
      printDebug(".");
    }

    if(WiFi.status() != WL_CONNECTED) {
        printDebug("[ANTARES] Could not connect to " + SSID + ".\n");
        return false;
    }
    else {
        WiFi.setAutoReconnect(true);
        printDebug("\n[ANTARES] WiFi Connected!\n");
        printDebug("[ANTARES] IP Address: " + ipToString(WiFi.localIP()) + "\n");
        return true;
    }
}



void AntaresESP8266MQTT::printDebug(String text) {
    if(_debug) {
        Serial.print(text);
    }
}

bool AntaresESP8266MQTT::setDebug(bool trueFalse) {
    _debug = trueFalse;
}

String AntaresESP8266MQTT::ipToString(IPAddress ip) {
    String s="";
    for (int i=0; i<4; i++)
      s += i  ? "." + String(ip[i]) : String(ip[i]);
    return s;
}

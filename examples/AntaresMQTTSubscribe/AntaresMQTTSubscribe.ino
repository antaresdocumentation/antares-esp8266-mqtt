#include <AntaresESP8266MQTT.h>

#define ACCESSKEY "your-access-key"
#define WIFISSID "your-wifi-ssid"
#define PASSWORD "your-wifi-password"

#define projectName = "your-project-name";
#define deviceName = "your-device-name";

AntaresESP8266MQTT antares(ACCESSKEY);

void callback(char topic[], byte payload[], unsigned int length) {
  String topicString = String(topic);
  String payloadString = antares.byteToString(payload, length);
  
  Serial.println("[ANTARES] New Mesage: ");
  Serial.println(topicString);
  Serial.println(payloadString);
}

void setup() {
  Serial.begin(115200);
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID, PASSWORD);
  antares.setMqttServer();
  antares.setCallback(callback);
}
void loop() {
  antares.checkMqttConnection();
}

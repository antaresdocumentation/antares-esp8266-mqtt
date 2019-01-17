#include <AntaresESP8266MQTT.h>

#define ACCESSKEY "your-access-key"
#define WIFISSID "your-wifi-ssid"
#define PASSWORD "your-wifi-password"

#define projectName "your-project-name"
#define deviceName "your-device-name"

AntaresESP8266MQTT antares(ACCESSKEY);

void setup() {
  Serial.begin(115200);
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID, PASSWORD);
  antares.setMqttServer();
}
void loop() {
  antares.checkMqttConnection();

  antares.add("temperature", 30);
  antares.add("humidity", 75);
  antares.add("message", "Hello World!");
  antares.add("temperature", 45);
  antares.printData();
  antares.publish(projectName, deviceName);
  delay(5000);
}

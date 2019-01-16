#include <AntaresESP8266MQTT.h>

#define ACCESSKEY "your-access-key"
#define WIFISSID "your-wifi-ssid"
#define PASSWORD "your-wifi-password"

#define projectName = "your-project-name";
#define deviceName = "your-device-name";

AntaresESP8266MQTT antares(ACCESSKEY);

void setup() {
	Serial.begin(115200);
	antares.setDebug(true);
	antares.wifiConnection(WIFISSID, PASSWORD);
	antares.setMqttServer();
}
void loop() {
  antares.checkMqttConnection();  
}

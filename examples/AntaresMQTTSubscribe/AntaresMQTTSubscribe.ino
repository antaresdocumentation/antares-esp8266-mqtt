/*
    This is an example sketch to subscribe to MQTT data on ESP8266
    via the Antares IoT Platform.

    MQTT server & port:
    platform.antares.id, port 1338

    MQTT topic:
    /oneM2M/req/your-access-key/antares-cse/json

    The main function in this sketch is the callback function,
    which will be fired every time a new message is published
    to the topic.

    For more information, please visit https://antares.id/id/docs.html
*/

#include <AntaresESP8266MQTT.h>

#define ACCESSKEY "your-access-key"
#define WIFISSID "your-wifi-ssid"
#define PASSWORD "your-wifi-password"

#define projectName "your-project-name"
#define deviceName "your-device-name"

AntaresESP8266MQTT antares(ACCESSKEY);

void callback(char topic[], byte payload[], unsigned int length) {
  /*
    Get the whole received data, including the topic,
    and parse the data according to the Antares data format.
  */
  antares.get(topic, payload, length);

  Serial.println("New Message!");
  // Print topic and payload
  Serial.println("Topic: " + antares.getTopic());
  Serial.println("Payload: " + antares.getPayload());
  // Print individual data
  Serial.println("Temperature: " + String(antares.getInt("temperature")));
  Serial.println("Humidity: " + String(antares.getInt("humidity")));
  Serial.println("Wind speed: " + String(antares.getFloat("wind_speed")));
  Serial.println("Rain level: " + String(antares.getFloat("rain_level")));
  Serial.println("Latitude: " + antares.getString("latitude"));
  Serial.println("Longitude: " + antares.getString("longitude"));
}

void setup() {
  Serial.begin(115200);
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID, PASSWORD);
  antares.setMqttServer();
  antares.setCallback(callback);
}
void loop() {
  /*
    Check if we're still connected to the MQTT broker/server.
    If disconnected, the device will try to reconnect.
  */
  antares.checkMqttConnection();
}

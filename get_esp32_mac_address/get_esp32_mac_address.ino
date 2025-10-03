#include <WiFi.h>

void setup() {
	Serial.begin(115200);
	WiFi.mode(WIFI_STA);
  	WiFi.begin();
  	String macAddress = WiFi.macAddress();
  	Serial.println("ESP32 MAC Address: " + macAddress);
}
void loop() {}

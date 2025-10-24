#include <WiFi.h>

String macAddress;

void setup() {
	Serial.begin(115200);
	Serial.println("Started");

	WiFi.mode(WIFI_STA);
	Serial.print("Receiver MAC: ");
	Serial.println(WiFi.macAddress());
	Serial.print("Channel: ");
	Serial.println(WiFi.channel()); 
  macAddress = WiFi.macAddress();
	Serial.println("ESP32 MAC Address: " + macAddress);
}
void loop() {
	Serial.println("ESP32 MAC Address: " + macAddress);
}

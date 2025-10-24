void setup() {
  Serial.begin(115200);                     // USB serial monitor
  Serial1.begin(9600, SERIAL_8N1, 16, 15);  // RX=16, TX=15
  Serial.println("ESP32 Transmitter Started");
}

void loop() {
  String message = "Hello STM32!\n";
  Serial1.print(message);      // Send to STM32
  Serial.println("Sent: " + message);
  delay(1000);
}
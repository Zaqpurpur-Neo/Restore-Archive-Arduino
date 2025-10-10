void setup() {
  Serial.begin(115200);
  Serial1.begin(115200); // RX1=19, TX1=18
}

void loop() {
  if (Serial1.available()) {
    Serial.print("From ESP32: ");
    while (Serial1.available()) {
      Serial.print((char)Serial1.read());
    }
    Serial.println();
  }

  Serial1.println("Hello from STM32");
  delay(1000);
}

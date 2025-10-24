void setup() {
  Serial.begin(115200);   // USB serial for monitor
  Serial1.begin(9600);    // Default UART (check your STM32 board)
  Serial.println("STM32 Receiver Ready");
}

void loop() {
  //if (Serial1.available()) {
    String data = Serial1.readStringUntil('\n');
    Serial.print("Received: ");
    Serial.println(data);
  //}
}
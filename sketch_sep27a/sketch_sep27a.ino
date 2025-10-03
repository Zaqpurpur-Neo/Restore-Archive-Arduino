#define BAUD_RATE 9600

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial);

  Serial1.begin(BAUD_RATE);
}

void loop() {
  if (Serial1.available()) {
    String received = Serial1.readStringUntil('\n');
    Serial.print("Received from ESP32: ");
    Serial.println(received);
  }
}

#define pin_rx 9
#define pin_tx 10

#define BAUD_RATE 9600

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial);

  Serial1.begin(BAUD_RATE);
}

void loop() {
  Serial1.println("DATA ESP32");
  Serial.println("Sent: DATA ESP32");
  delay(1000);
}

#define OUT
#define IN 

#define PIN_OUT(p) pinMode((p), OUTPUT) 
#define PIN_IN(p) pinMode((p), INPUT) 
#define WRITE_H(p) digitalWrite((p), HIGH)
#define WRITE_L(p) digitalWrite((p), LOW)

void setup() {
  PIN_OUT(PC13);
}

void loop() {
  WRITE_H(PC13);
  Serial.println(PC13);
  delay(100);
  WRITE_L(PC13);
  delay(100);
}
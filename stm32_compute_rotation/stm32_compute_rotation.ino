#define BAUD_RATE_STM32 96000

typedef struct JoyAnalog {
	int16_t lx;
	int16_t ly;
	int16_t rx;
	int16_t ry;
} JoyAnalog;

void setup() {
	Serial.begin(115200);
	while(!Serial);

	Serial1.begin(BAUD_RATE_STM32);
}

void loop() {
  if (Serial1.available()) {
	  JoyAnalog analog;
	  Serial1.readBytes((char*)&analog, sizeof(analog));

	  Serial.print("[Analog]");
	  Serial.print(" LX: "); Serial.print(analog.lx);
	  Serial.print(" LY: "); Serial.print(analog.ly);
	  Serial.print(" RX: "); Serial.print(analog.rx);
	  Serial.print(" RY: "); Serial.println(analog.ry);
 
  }
}

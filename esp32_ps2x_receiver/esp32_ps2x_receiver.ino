#include <esp_now.h>
#include <WiFi.h>

#define BAUD_RATE_STM32 96000

typedef enum ActionType {
	BTN_UP = 0,
	BTN_RIGHT,
	BTN_DOWN,
	BTN_LEFT,
	BTN_UNKNOWN
} ActionType;

typedef struct JoyAnalog {
	int16_t lx;
	int16_t ly;
	int16_t rx;
	int16_t ry;
} JoyAnalog;

typedef struct Action {
	ActionType action;
	JoyAnalog joyAnalog;
	bool sendStick;
} Action;

void OnDataRecv(const esp_now_recv_info *info, const uint8_t *incomingDataBytes, int len) {
	Action actionComing;
	memcpy(&actionComing, incomingDataBytes, sizeof(actionComing));

	if(actionComing.sendStick) {
		Serial.print("[Stick]: ");
		JoyAnalog analog = actionComing.joyAnalog;
		Serial1.write((uint8_t*)&analog, sizeof(analog));
    }

	Serial.print("[Action]: ");
	switch (actionComing.action) {
		case BTN_UP:
			Serial.println("BTN_UP");
			break;
		case BTN_LEFT:
			Serial.println("BTN_LEFT");
			break;
		case BTN_RIGHT:
			Serial.println("BTN_RIGHT");
			break;
		case BTN_DOWN:
			Serial.println("BTN_DOWN");
			break;
		default:
			// Serial.println("UNKNOWN");
			break;
	}
}

void setup() {
	Serial.begin(115200);

	Serial1.begin(BAUD_RATE_STM32);

	WiFi.mode(WIFI_STA);  
	Serial.print("Receiver MAC: ");
	Serial.println(WiFi.macAddress());
	Serial.print("Channel: ");
	Serial.println(WiFi.channel()); 
	  
	if (esp_now_init() != ESP_OK) {
		Serial.println("Gagal inisialisasi ESP-NOW");
		return;
	}  
	esp_now_register_recv_cb(OnDataRecv);
}

void loop() {}

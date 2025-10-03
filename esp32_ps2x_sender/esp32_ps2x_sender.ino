#include <PS2X_lib.h>  //for v1.6
#include <esp_now.h>
#include <WiFi.h>

#define PS2_DAT 19  //MISO  19
#define PS2_CMD 23  //MOSI  23
#define PS2_SEL  5  //SS     5
#define PS2_CLK 18  //SLK   18  
						
#define pressures   false
#define rumble      false

PS2X ps2x;

int error = -1;
byte type = 0;
byte vibrate = 0;
int tryNum = 1;

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

uint8_t broadcastAddress[] = {0xFC, 0x01, 0x2C, 0xD1, 0x7C, 0x8C};

void setup_ps2x() {
  Serial.begin(115200);

  while (error != 0) {
    delay(1000); 
    error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

    Serial.print("#try config ");
    Serial.println(tryNum);
    tryNum++;
  }

  Serial.println(ps2x.Analog(1), HEX);

  type = ps2x.readType();
  switch(type) {
    case 0:
      Serial.println(" Unknown Controller type found ");
      break;
    case 1:
      Serial.println(" DualShock Controller found ");
      break;
    case 2:
      Serial.println(" GuitarHero Controller found ");
      break;
	case 3:
      Serial.println(" Wireless Sony DualShock Controller found ");
      break;
   }
}

void OnDataSent(const wifi_tx_info_t *info, esp_now_send_status_t status) {
	Serial.print(" | Status: ");
	Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Terkirim" : "Gagal");
}

void setup_sender() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Gagal init ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 1;
  peerInfo.encrypt = false;

  esp_err_t result = esp_now_add_peer(&peerInfo);
  switch(result) {
	  case ESP_OK:
		  Serial.println("Peer berhasil ditambahkan");
		  break;
	  case ESP_ERR_ESPNOW_NOT_INIT:
		  Serial.println("ESP-NOW belum diinit");
		  break;
	  case ESP_ERR_ESPNOW_ARG:
		  Serial.println("Argumen salah");
		  break;
	  case ESP_ERR_ESPNOW_FULL:
		  Serial.println("Daftar peer penuh");
		  break;
	  case ESP_ERR_ESPNOW_NO_MEM:
		  Serial.println("Memori tidak cukup");
		  break;
	  case ESP_ERR_ESPNOW_EXIST:
		  Serial.println("Peer sudah ada");
		  break;
	  default:
		  Serial.print("Error lain: ");
		  Serial.println(result);
  }
}

void setup() {
	setup_ps2x();
	setup_sender();
}

void loop() {
	if(type == 1) {
		ps2x.read_gamepad(false, vibrate);

		Action act = {};
		act.action = BTN_UNKNOWN;

		if(ps2x.Button(PSB_PAD_UP)) {
			act.action = BTN_UP;
		}
		if(ps2x.Button(PSB_PAD_RIGHT)){
			act.action = BTN_RIGHT;
		}
		if(ps2x.Button(PSB_PAD_LEFT)){
			act.action = BTN_LEFT;
		}
		if(ps2x.Button(PSB_PAD_DOWN)){
			act.action = BTN_DOWN;
		}

		act.sendStick = true;
		act.joyAnalog.lx = ps2x.Analog(PSS_LX);
		act.joyAnalog.ly = ps2x.Analog(PSS_LY);
		act.joyAnalog.rx = ps2x.Analog(PSS_RX);
		act.joyAnalog.ry = ps2x.Analog(PSS_RY);
		
		esp_now_send(NULL, (uint8_t*) &act, sizeof(Action));
	}
	delay(100);
}

#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0x68, 0x25, 0xDD, 0x47, 0x72, 0x18};

typedef struct struct_message {
  int id;
  float value;
} struct_message;

struct_message myData;

void OnDataSent(const wifi_tx_info_t *info, esp_now_send_status_t status) {
  if (info) {
    char macStr[18];
    snprintf(macStr, sizeof(macStr),
             "%02X:%02X:%02X:%02X:%02X:%02X",
             info->des_addr[0], info->des_addr[1], info->des_addr[2],
             info->des_addr[3], info->des_addr[4], info->des_addr[5]);

    Serial.print("Data ke: ");
    Serial.print(macStr);
  } else {
    Serial.print("Data ke: [broadcast]");
  }

  Serial.print(" | Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Terkirim" : "Gagal");
}

void setup() {
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
  if (result == ESP_OK) {
    Serial.println("Peer berhasil ditambahkan");
  } else if (result == ESP_ERR_ESPNOW_NOT_INIT) {
    Serial.println("ESP-NOW belum diinit");
  } else if (result == ESP_ERR_ESPNOW_ARG) {
    Serial.println("Argumen salah");
  } else if (result == ESP_ERR_ESPNOW_FULL) {
    Serial.println("Daftar peer penuh");
  } else if (result == ESP_ERR_ESPNOW_NO_MEM) {
    Serial.println("Memori tidak cukup");
  } else if (result == ESP_ERR_ESPNOW_EXIST) {
    Serial.println("Peer sudah ada");
  } else {
    Serial.print("Error lain: ");
    Serial.println(result);
  }

  myData.id = 1;
  myData.value = 42.5;
}

void loop() {
  esp_now_send(NULL, (uint8_t *) &myData, sizeof(myData)); // NULL = broadcast
  delay(2000);
}

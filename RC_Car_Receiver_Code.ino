#include <esp_now.h>
#include <WiFi.h>
#define UPLEFT1 5
#define UPLEFT2 6
#define UPRIGHT1 15
#define UPRIGHT2 7
#define BACKLEFT1 18
#define BACKLEFT2 8
#define BACKRIGHT1 17
#define BACKRIGHT2 16

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  int gest;
} struct_message;
        
// Create a struct_message called myData
struct_message myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Char: ");
  Serial.println(myData.gest);
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
  pinMode(UPLEFT1, OUTPUT);
  pinMode(UPLEFT2, OUTPUT);
  pinMode(UPRIGHT1, OUTPUT);
  pinMode(UPRIGHT2, OUTPUT);
  pinMode(BACKLEFT1, OUTPUT);
  pinMode(BACKLEFT2, OUTPUT);
  pinMode(BACKRIGHT1, OUTPUT);
  pinMode(BACKRIGHT2, OUTPUT);
}

void loop() {
  // DOWN
  if (myData.gest == 2) {
    Serial.println("1");
    analogWrite(UPLEFT1, 0);
    analogWrite(UPLEFT2, 0);
    analogWrite(UPRIGHT1, 0);
    analogWrite(UPRIGHT2, 0);
    analogWrite(BACKLEFT1, 0);
    analogWrite(BACKLEFT2, 0);
    analogWrite(BACKRIGHT1, 0);
    analogWrite(BACKRIGHT2, 0);
  }
  // UP
  if (myData.gest == 3) {
    Serial.println("2");
    analogWrite(UPLEFT1, 50);
    analogWrite(UPLEFT2, 0);
    analogWrite(UPRIGHT1, 255);
    analogWrite(UPRIGHT2, 0);
    analogWrite(BACKLEFT1, 255);
    analogWrite(BACKLEFT2, 0);
    analogWrite(BACKRIGHT1, 255);
    analogWrite(BACKRIGHT2, 0);
  }
  // FAR
  if (myData.gest == 4) {
    Serial.println("3");
    analogWrite(UPLEFT1, 0);
    analogWrite(UPLEFT2, 150);
    analogWrite(UPRIGHT1, 0);
    analogWrite(UPRIGHT2, 255);
    analogWrite(BACKLEFT1, 255);
    analogWrite(BACKLEFT2, 0);
    analogWrite(BACKRIGHT1, 0);
    analogWrite(BACKRIGHT2, 255);
  }
  // LEFT
  if (myData.gest == 5) {
    Serial.println("4");
    analogWrite(UPLEFT1, 0);
    analogWrite(UPLEFT2, 0);
    analogWrite(UPRIGHT1, 255);
    analogWrite(UPRIGHT2, 0);
    analogWrite(BACKLEFT1, 255);
    analogWrite(BACKLEFT2, 0);
    analogWrite(BACKRIGHT1, 255);
    analogWrite(BACKRIGHT2, 0);
    delay(500);
    analogWrite(UPLEFT1, 150);
    analogWrite(UPLEFT2, 0);
    analogWrite(UPRIGHT1, 255);
    analogWrite(UPRIGHT2, 0);
    analogWrite(BACKLEFT1, 255);
    analogWrite(BACKLEFT2, 0);
    analogWrite(BACKRIGHT1, 255);
    analogWrite(BACKRIGHT2, 0);
  }
  // RIGHT
  if (myData.gest == 6) {
    Serial.println("5");
    analogWrite(UPLEFT1, 150);
    analogWrite(UPLEFT2, 0);
    analogWrite(UPRIGHT1, 0);
    analogWrite(UPRIGHT2, 0);
    analogWrite(BACKLEFT1, 255);
    analogWrite(BACKLEFT2, 0);
    analogWrite(BACKRIGHT1, 255);
    analogWrite(BACKRIGHT2, 0);
    delay(500);
    analogWrite(UPLEFT1, 150);
    analogWrite(UPLEFT2, 0);
    analogWrite(UPRIGHT1, 255);
    analogWrite(UPRIGHT2, 0);
    analogWrite(BACKLEFT1, 255);
    analogWrite(BACKLEFT2, 0);
    analogWrite(BACKRIGHT1, 255);
    analogWrite(BACKRIGHT2, 0);
  }
}
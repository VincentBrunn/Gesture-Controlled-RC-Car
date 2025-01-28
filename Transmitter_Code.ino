#include <esp_now.h>
#include <WiFi.h>
#include <SparkFun_APDS9960.h>
#include <Wire.h>
#define APDS9960_INT 5  // Needs to be an interrupt pin
#define I2C_SDA 15
#define I2C_SCL 7
SparkFun_APDS9960 apds = SparkFun_APDS9960();
volatile bool isr_flag = false;
void interruptRoutine() {
  isr_flag = true;
}

// Receiver MAC
uint8_t broadcastAddress[] = { 0x48, 0x27, 0xE2, 0x2F, 0xBD, 0x64 };  // Unit #1

// Define variables to store BME280 readings to be sent
float gesture;
float humidity;
float pressure;

// Variable to store if sending data was successful
String success;

//Must match the receiver structure
typedef struct struct_message {
  float gest;
} struct_message;
// Create a struct_message called BME280Readings to hold sensor readings
struct_message APDSReadings;

esp_now_peer_info_t peerInfo;

enum Apds9960 {
  APDS_UP,
  APDS_DOWN,
  APDS_LEFT,
  APDS_RIGHT,
  APDS_NEAR,
  APDS_FAR,
  APDS_NONE,
  APDS_BLUE,
  APDS_GREEN,
  APDS_RED,
  APDS_WHITE,
};


// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
  Serial.println();
  Serial.println(F("--------------------------------"));
  Serial.println(F("APDS-9960 - GestureTest"));
  Serial.println(F("--------------------------------"));

  Wire.begin(I2C_SDA, I2C_SCL);
  // Set interrupt pin as input
  pinMode(APDS9960_INT, INPUT);

  // Initialize interrupt service routine
  attachInterrupt(APDS9960_INT, interruptRoutine, FALLING);

  // Initialize APDS-9960 (configure I2C and initial values)
  if (apds.init()) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }

  // Start running the APDS-9960 gesture sensor engine
  if (apds.enableGestureSensor(true)) {
    Serial.println(F("Gesture sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during gesture sensor init!"));
  }

  // Init BME280 sensor
  bool status = true;
  // status = bme.begin(0x76);
  if (!status) {
    // Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1)
      ;
  }
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

}

void handleGesture() {
  while (apds.isGestureAvailable()) {
    switch (apds.readGesture()) {
      case DIR_UP:
        Serial.println("UP");
        gesture = APDS_UP;
        break;
      case DIR_DOWN:
        Serial.println("DOWN");
        gesture = APDS_DOWN;
        break;
      case DIR_LEFT:
        Serial.println("LEFT");
        gesture = APDS_LEFT;
        break;
      case DIR_RIGHT:
        Serial.println("RIGHT");
        gesture = APDS_RIGHT;
        break;
      case DIR_NEAR:
        Serial.println("NEAR");
        gesture = APDS_NEAR;
        break;
      case DIR_FAR:
        Serial.println("FAR");
        gesture = APDS_FAR;
        break;
      default:
        Serial.println("NONE");
        delay(5);
    }
  }
}

void loop() {
  if (isr_flag == true) {
    isr_flag = false;
    handleGesture();
  }

  // Set values to send
  APDSReadings.gest = gest;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&APDSReadings, sizeof(APDSReadings));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
  } else {
    Serial.println("Error sending the data");
  }
  delay(2000);
}

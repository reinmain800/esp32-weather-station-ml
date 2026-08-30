/*
Temperature, Pressure, and Humidity reading
by Maximilian Can Mueller
2026

Receives Temperature, Pressure, and Humidity readings
from a BME280 and prints them to the Serial Monitor.

This code is in the Public Domain
*/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <SX126x.h>
#include <SPI.h>

// create BME280 object
Adafruit_BME280 bme_OD;

// create LoRa object
SX126x LoRa;

// define BME280 pins
const int SDAPin = 8;
const int SCLPin = 9;

// define E22-400M22S pins
#define LORA_NSS 10
#define LORA_SCK 12
#define LORA_MOSI 11
#define LORA_MISO 13
#define LORA_NRST 14
#define LORA_BUSY 15
#define LORA_DIO1 16

#define LORA_FREQUENCY 433000000

//sets up deep sleep timer
const int TIME_OF_SLEEP = 300;                        
unsigned long long uS_TO_S_FACTOR = 1000000; //factor to convert from microseconds  to seconds 

void setup() {
  Serial.begin(115200); //set to baud rate 115200
  delay(1000);

  Wire.begin(SDAPin, SCLPin); //Begin I2C communication


  //waits for BME280 initialisation
  while (!bme_OD.begin(0x76)) {
    delay(5);
  }

  //reads temperature, humidity and pressure and assigns to float values
  float temperature_OD = bme_OD.readTemperature();
  float humidity_OD = bme_OD.readHumidity();
  float pressure_OD = bme_OD.readPressure() / 100.0F;

  spiInitialise();

  //sendData function
  sendData(temperature_OD, humidity_OD, pressure_OD);

  SPI.end();

  //initialises deep sleep to save power
  esp_sleep_enable_timer_wakeup(TIME_OF_SLEEP * uS_TO_S_FACTOR);  
  Serial.flush();                                              
  esp_deep_sleep_start();   
}

void spiInitialise() {
  SPI.begin(
    LORA_SCK,
    LORA_MISO,
    LORA_MOSI,
    LORA_NSS
  );

  LoRa.setSPI(SPI, LORA_NSS);
  LoRa.setPins(
    LORA_NRST,
    LORA_BUSY,
    LORA_DIO1
  );

  while (!LoRa.begin()) {
    delay(5);
  }

  LoRa.setFrequency(LORA_FREQUENCY);

  LoRa.setLoRaModulation(
    7,       // Spreading Factor
    125000,  // Bandwidth
    5        // Coding Rate 4/5
  );

  LoRa.setLoRaPacket(
    8,       // Preamble
    0,       // Explicit header
    true     // CRC
  );

  LoRa.setTxPower(17);

}


void sendData(float temperature_OD, float humidity_OD, float pressure_OD) {

  char message[100];

  snprintf(
    message,
    sizeof(message),
    "T_OD=%.2f,P_OD=%.2f,H_OD=%.2f",
    temperature_OD,
    pressure_OD,
    humidity_OD
  );

  LoRa.beginPacket();

  LoRa.write(
    (uint8_t*)message,
    strlen(message)
  );

  LoRa.endPacket();

  LoRa.sleep();
}


void loop() {

}
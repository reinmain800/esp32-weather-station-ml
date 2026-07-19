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
#include <WiFi.h>

// Create BME280 object
Adafruit_BME280 bme;

// WiFi username and password
const char* ssid = "reinmain";
const char* password = "reinmain800";

// I²C pins
const uint8_t SCL_PIN = 9;
const uint8_t SDA_PIN = 8;

// Time between readings (milliseconds)
const unsigned long delayTime = 10000;


// Initialize WiFi
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  int attempts = 0;

  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    Serial.print(".");
    delay(1000);
    attempts++;
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } 
  else {
    Serial.println("Failed to connect to WiFi.");
  }
}


// Initialize BME280
void initBME280() {
  Wire.begin(SDA_PIN, SCL_PIN);

  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor. Check wiring!");
    while (1);
  }

  Serial.println("BME280 initialized successfully.");
  Serial.println();
}


// Print sensor values
void printValues() {
  float temperature = bme.readTemperature();
  float pressure = bme.readPressure() / 100.0F;
  float humidity = bme.readHumidity();

  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.println();
}


void setup() {
  Serial.begin(115200);
  delay(1000);

  initBME280();
  initWiFi();
}


void loop() {
  printValues();
  delay(delayTime);
}
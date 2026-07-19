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
#include <esp_sleep.h>

// Create BME280 object
Adafruit_BME280 bme;

// I²C pins
const int SCLPin = 9;
const int SDAPin = 8;

// Time between readings (milliseconds)
const unsigned long delayTime = 10000;

void setup() {
  Serial.begin(115200);
  delay(10000);

  // Initialize I²C
  Wire.begin(SDAPin, SCLPin);

  // Initialize the BME280
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor. Check wiring!");
    while (1);
  }

  Serial.println("BME280 initialized successfully.");
  Serial.println();
}

void loop() {
  printValues();
  delay(delayTime);
}

void printValues() {
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" °C");

  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println();
}
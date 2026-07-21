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

// create BME280 object
Adafruit_BME280 bme;

// set pins used on ESP32
const int SDAPin = 8;
const int SCLPin = 9;

//variable containing delay between readings
const int delayTime = 300000;

void setup() {
  Serial.begin(115200); //set to baud rate 115200

  Wire.begin(SDAPin, SCLPin); //Begin I2C communication

  if (bme.begin(0x76) == false) {
    Serial.println("Could not connect to BME280 sensor"); //checks for successful connection
  }
  Serial.println("BME280 connected successfully");
}

//utilising bme functions to access and print temperature, humidity, and pressure under the function printValues()
void printValues() { 
  Serial.print("Temperature: ");
  Serial.print(bme.readTemperature());
  Serial.println(" ˚C");

  Serial.print("Humidity: ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.print("Pressure: ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");
}

//loops print with 5 minute delay
void loop() {
  printValues();
  delay(delayTime);
  Serial.println();
}

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
#include <HTTPClient.h>

// create BME280 object
Adafruit_BME280 bme;

// set pins used on ESP32
const int SDAPin = 8;
const int SCLPin = 9;

//assigning values to wifi ssid and password
const char* ssid = "YOUR SSID";
const char* password = "YOUR PASSWORD";

const char* serverName = "http://YOUR_FLASK_SERVER_ADDRESS/receive_data"; // server name


void setup() {
  Serial.begin(115200); //set to baud rate 115200

  Wire.begin(SDAPin, SCLPin); //Begin I2C communication

  WiFi.begin(ssid, password); //connecting to wifi

  Serial.print("Connecting to WiFi"); 

  unsigned long startTime = millis();

  //wifi conenction error while loop
  while (WiFi.status() != WL_CONNECTED) {

      if (millis() - startTime > 20000) {
          Serial.println("\nWiFi connection unsuccessful.");
          break;
      }

      delay(500);
      Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\nWiFi connected!");
      Serial.print("IP Address: ");
      Serial.println(WiFi.localIP());
  }

  //checking BME280 connection
  if (bme.begin(0x76) == false) {
    Serial.println("Could not connect to BME280 sensor"); //checks for successful connection
  }

}


void sendData(float temperature, float humidity, float pressure) {
  WiFiClient client;
  HTTPClient http;

  http.begin(client, serverName);

  http.addHeader("Content-Type", "application/json");

  String httpRequestData = "{";
  httpRequestData += "\"temperature\":";
  httpRequestData += temperature;
  httpRequestData += ",\"humidity\":";
  httpRequestData += humidity;
  httpRequestData += ",\"pressure\":";
  httpRequestData += pressure;
  httpRequestData += "}";

  int httpResponseCode = http.POST(httpRequestData);
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);

  http.end();
}


//setting up delay between measurements
unsigned long previousTime = 0;
const unsigned long interval = 300000; 


//sends json packets with 5 minute delay
void loop() {
  unsigned long currentTime = millis();

  if (currentTime - previousTime >= interval) {
    float temperature = bme.readTemperature();
    float humidity = bme.readHumidity();
    float pressure = bme.readPressure() / 100.0F;
    Serial.println();
    sendData(temperature, humidity, pressure);
    previousTime = currentTime;
  }
  delay(100);
}

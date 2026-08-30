/*
Temperature, Pressure, and Humidity reading
by Maximilian Can Mueller
2026

Receives Temperature, Pressure, and Humidity readings
from a BME280 and sends to flask server.

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

//sets up deep sleep timer
const int TIME_OF_SLEEP = 300;                        
unsigned long long uS_TO_S_FACTOR = 1000000; //factor to convert from microseconds  to seconds 

//assigning values to wifi ssid and password
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

const char* serverName = "http://YOUR_FLASK_IP:5000/receive_data"; // server name


void setup() {
  Serial.begin(115200); //set to baud rate 115200

  Wire.begin(SDAPin, SCLPin); //Begin I2C communication
  WiFi.begin(ssid, password); //connecting to wifi

  //waits for wifi connection
  while (WiFi.status() != WL_CONNECTED) { 
    delay(5);
  }

  //waits for BME280 initialisation
  while (bme.begin(0x76) != true) {
    delay(5);
  }

  //reads temperature, humidity and pressure and assigns to float values
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F;

  //sendData function
  sendData(temperature, humidity, pressure);

  //disconnect from WiFi
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  //initialises deep sleep to save power
  esp_sleep_enable_timer_wakeup(TIME_OF_SLEEP * uS_TO_S_FACTOR);  
  Serial.flush();                                              
  esp_deep_sleep_start();   
}


void sendData(float temperature, float humidity, float pressure) {
  WiFiClient client;
  HTTPClient http;

  http.begin(client, serverName);

  http.addHeader("Content-Type", "application/json");

  String httpRequestData = "{";
  httpRequestData += "\"temperature\":"; httpRequestData += temperature;
  httpRequestData += ",\"humidity\":";    httpRequestData += humidity;
  httpRequestData += ",\"pressure\":";    httpRequestData += pressure;
  httpRequestData += "}";

  int httpResponseCode = http.POST(httpRequestData);
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode); //Successful transmission if HTTP response code = 202

  http.end();
}


void loop() {

}
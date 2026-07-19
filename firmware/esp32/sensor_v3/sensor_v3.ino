/*
ESP32 Weather Station
Temperature, Pressure, and Humidity sent via WiFi
by Maximilian Can Mueller
2026
*/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Create BME280 object
Adafruit_BME280 bme;

// WiFi credentials
const char* ssid = "reinmain";
const char* password = "reinmain800";

// Flask server address
const char* serverURL = "http://192.168.110.207/weather";

// I2C pins
const uint8_t SCL_PIN = 9;
const uint8_t SDA_PIN = 8;

// Time between measurements
const unsigned long delayTime = 300000;


// Initialize WiFi
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println();
  Serial.println("WiFi connected!");

  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP());
}


// Initialize BME280
void initBME280() {
  Wire.begin(SDA_PIN, SCL_PIN);

  if (!bme.begin(0x76)) {
    Serial.println("Could not find BME280 sensor!");
    while (1);
  }

  Serial.println("BME280 initialized.");
}


// Send weather data to Flask
void sendData() {

  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;

    http.begin(serverURL);

    http.addHeader("Content-Type", "application/json");


    float temperature = bme.readTemperature();
    float pressure = bme.readPressure() / 100.0F;
    float humidity = bme.readHumidity();


    String jsonData = "{";
    jsonData += "\"temperature\":" + String(temperature) + ",";
    jsonData += "\"pressure\":" + String(pressure) + ",";
    jsonData += "\"humidity\":" + String(humidity);
    jsonData += "}";


    Serial.println("Sending data:");
    Serial.println(jsonData);


    int responseCode = http.POST(jsonData);


    if (responseCode > 0) {
      Serial.print("Server response: ");
      Serial.println(responseCode);
    } 
    else {
      Serial.print("Error sending data: ");
      Serial.println(responseCode);
    }


    http.end();

  } else {
    Serial.println("WiFi disconnected");
  }
}


void setup() {

  Serial.begin(115200);
  delay(1000);

  initBME280();
  initWiFi();

}


void loop() {

  sendData();

  delay(delayTime);

}
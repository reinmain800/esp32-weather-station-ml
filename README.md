# ESP32 Weather Station with Machine Learning

## Goal
Build an autonomous weather monitoring station initially using an ESP32 and BME280 sensor, collect environmental data, and develop a machine learning model for weather prediction.

## Hardware
- ESP32-S3-WROOM-1
- BME280 temperature, pressure, humidity sensor

## Potential additions
- Wind speed sensor (Anemometer)
- Rain gauge
- 18650 battery

## Current Progress
- [x] ESP32 setup
- [x] BME280 communication
- [x] Python Flask server
- [x] Wi-Fi data transmission
- [X] ESP32 deep sleep energy usage reduction
- [ ] Storing data in SQLite database
- [ ] Custom Rain Gauge
- [ ] Implement wind vane and anemometer
- [ ] 3D printed casing
- [ ] Indoor and Outdoor BME280
- [ ] Soldering components
- [ ] Machine learning model

## Future Improvements
- Solar power
- Go from HTTP POST using a Flask server to LoRa module 

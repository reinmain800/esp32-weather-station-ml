from flask import Flask, request
from datetime import datetime

app = Flask(__name__)

@app.route('/')
def hello_world():
    return 'Weather server running'


@app.route('/weather', methods=['POST'])
def receive_weather():
    data = request.json

    temperature = data["temperature"]
    humidity = data["humidity"]
    pressure = data["pressure"]

    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")



    print("Received weather data:")
    print(f"Temperature: {temperature} °C")
    print(f"Humidity: {humidity} %")
    print(f"Pressure: {pressure} hPa")
    print(timestamp)
    print()

    return "Data received successfully"


app.run(host="0.0.0.0", port=80)
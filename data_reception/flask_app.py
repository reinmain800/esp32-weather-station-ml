from flask import Flask, request
import sqlite3


def send_data(temperature, humidity, pressure):
    """Creates database and sends sensor data to database"""

    conn = sqlite3.connect('data/weather_measurements.db')
    c = conn.cursor()

    c.execute("""CREATE TABLE IF NOT EXISTS weather_measurements(
                ID INTEGER PRIMARY KEY AUTOINCREMENT,
                Timestamp DATETIME DEFAULT (datetime('now', '+8 hours')),
                Temperature real,
                Humidity real,
                Pressure real
                )""")

    c.execute("""
                INSERT INTO weather_measurements (Temperature, Humidity, Pressure)
                VALUES(:temperature, :humidity, :pressure)
                """,
                {
                    'temperature': temperature,
                    'humidity': humidity,
                    'pressure': pressure
                }
    )
    conn.commit()
    conn.close()


app = Flask(__name__)

@app.route('/receive_data', methods = ['POST'])
def receive_data():
    """creates flask server which accepts HTTP POST requests and initiates data storage"""

    data = request.json

    if data is None:
        return "No JSON received", 400
    
    elif data:
        temperature = data['temperature']
        humidity = data['humidity']
        pressure = data['pressure']
    
        send_data(temperature, humidity, pressure)
        print("\nData successfully stored\n")

    return "", 202

#runs app
if __name__ == '__main__':
    app.run(host = '0.0.0.0', port = '5000', debug = False)



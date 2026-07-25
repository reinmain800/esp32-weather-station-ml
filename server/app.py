from flask import Flask, request

app = Flask(__name__)

@app.route('/receive_data', methods = ['POST'])
def receive_data():
    data = request.json

    if data is None:
        return "No JSON received", 400

    print(
        f"Temperature: {data['temperature']} °C\n"
        f"Humidity: {data['humidity']} %\n"
        f"Pressure: {data['pressure']} hPa"
    )

    return "Data received", 202

if __name__ == '__main__':
    app.run(host = '0.0.0.0', port = '5000', debug = True)

from LoRaRF import SX126x
import time


# define E22-400M22s pins

RESET = 22
BUSY = 23

SPI_BUS = 0
SPI_CS = 0
SPI_SPEED = 7800000

FREQUENCY = 433000000



# Create LoRa object

LoRa = SX126x()


# SPI
LoRa.setSPI(
    SPI_BUS,
    SPI_CS,
    SPI_SPEED
)



# GPIO
LoRa.setPins(
    RESET,
    BUSY,
    -1,
    -1,
    -1
)


# Start E22
if not LoRa.begin():
    time.sleep(0.005)


LoRa.setFrequency(
    FREQUENCY
)

LoRa.setLoRaModulation(
    7,
    125000,
    5
)

LoRa.setLoRaPacket(
    8,
    0,
    True
)

# Receive loop
while True:

    if LoRa.request():

        if LoRa.wait():

            length = LoRa.available()

            if length > 0:

                data = LoRa.read(length)

                message = bytes(data).decode(
                    "utf-8",
                    errors="replace"
                )

                print("Received:")
                print(message)

                print(
                    "RSSI:",
                    LoRa.packetRssi(),
                    "dBm"
                )

                print(
                    "SNR:",
                    LoRa.snr(),
                    "dB"
                )

                print("-----------------------------")
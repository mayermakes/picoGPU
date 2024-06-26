import smbus
import time
import random

# I2C address of the device we want to talk to
ID = 0x05

# Define colors
BLACK = 0x0000
BLUE = 0x001F
RED = 0xF800
GREEN = 0x07E0
CYAN = 0x07FF
MAGENTA = 0xF81F
YELLOW = 0xFFE0
WHITE = 0xFFFF

# Initialize the I2C bus
bus = smbus.SMBus(1)  # 1 indicates /dev/i2c-1

def i2ctransmit(IDs=ID, COM="text", TXT="nothing", colorcode=0xFFFF, locX=0, locY=0, wide=1, tall=1, inverter=0, rotation=0):
    message = f"{IDs},{COM},{TXT},{colorcode},{locX},{locY},{wide},{tall},{inverter},{rotation}"
    data = list(message.encode('utf-8'))
    bus.write_i2c_block_data(IDs, 0, data)
    time.sleep(0.5)

def setup():
    pass  # No setup required for smbus

def loop():
    random.seed(time.time())

    while True:
        i2ctransmit(ID, "fillscreen", "nothing", BLACK, 0, 0, 1, 1, 0, 0)
        time.sleep(1)
        i2ctransmit(ID, "text", "Hello World", WHITE, 0, 0, 1, 1, 0, 0)
        time.sleep(2)
        i2ctransmit(ID, "fillscreen", "nothing", random.randint(0x0000, 0xFFFF), 0, 0, 1, 1, 0, 0)
        time.sleep(1)
        i2ctransmit(ID, "setRotation", "Hello World", WHITE, 0, 0, 1, 1, 0, 1)
        i2ctransmit(ID, "text", "Weird world", WHITE, 20, 20, 4, 4, 0, 0)
        time.sleep(2)
        i2ctransmit(ID, "invertDisplay", "Hello World", WHITE, 0, 0, 1, 1, 1, 1)
        i2ctransmit(ID, "setRotation", "Hello World", WHITE, 0, 0, 1, 1, 0, 0)
        time.sleep(1)
        i2ctransmit(ID, "text", "ELEMENT14", WHITE, 50, 50, 4, 2, 0, 0)
        time.sleep(0.5)
        i2ctransmit(ID, "text", "presents", WHITE, 100, 100, 2, 4, 0, 0)
        time.sleep(0.5)
        i2ctransmit(ID, "invertDisplay", "Hello World", WHITE, 0, 0, 1, 1, 0, 0)
        time.sleep(1)
        i2ctransmit(ID, "fillscreen", "nothing", BLACK, 0, 0, 1, 1, 0, 0)
        for i in range(1000):
            i2ctransmit(ID, "drawPixel", "nothing", random.randint(0x0000, 0xFFFF), random.randint(0, 320), random.randint(0, 240), 1, 1, 0, 0)
            time.sleep(0.05)

if __name__ == "__main__":
    setup()
    loop()


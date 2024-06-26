#! /usr/bin/python
import argparse
import subprocess
from smbus import SMBus
import sys
i2cbus = SMBus(1)  # Create a new I2C bus
i2caddress = 0x05  # PseudoGpu ID

# Define colors
BLACK = 0x0000
BLUE = 0x001F
RED = 0xF800
GREEN = 0x07E0
CYAN = 0x07FF
MAGENTA = 0xF81F
YELLOW = 0xFFE0
WHITE = 0xFFFF
colorcode= 0xFFFF
parser = argparse.ArgumentParser(prog='PseudoGPUdriver_minimal',description='Sends text input to PseudoGPU', epilog='as seen on element14presents, CC-BY-SA ,MAYER MAKES e.U. 2024 ')
parser.add_argument('-c','--color', choices=['BLACK', 'WHITE', 'BLUE', 'RED' , 'GREEN', 'CYAN', 'MAGENTA', 'YELLOW' ], default= 'BLACK', help= 'choose the background color', action= 'store', dest= 'colorcode')
parser.add_argument('-x','--locX',  default= '0', help= 'location in X axis', action= 'store', dest= 'locX')
parser.add_argument('-y','--locY',  default= '0', help= 'location in Y axis', action= 'store', dest= 'locY')
parser.add_argument('-w','--wide',  default= '1', help= '(wide) width of text', action= 'store', dest= 'wide')
parser.add_argument('-t','--tall',  default= '1', help= '(tall) height of text', action= 'store', dest= 'tall')
parser.add_argument('-i','--invert',  default= '0',choices=[ 0, 1 ], help= 'invert output 0= no, 1= yes', action= 'store', dest= 'inverter')
parser.add_argument('-r','--rotate',  default= '0',choices=[ 0, 1, 2, 3 ], help= 'rotate output', action= 'store', dest= 'rotation')

 
args = parser.parse_args()
colorcode= args.colorcode
locX = args.locX
locY = args.locY
wide = args.wide
tall = args.tall
inverter= args.inverter
rotation= args.rotation

parser.print_help()
def i2ctransmit(IDs=i2caddress, COM="text", TXT="nothing", colorcode=0xFFFF, locX=0, locY=0, wide=1, tall=1, inverter=0, rotation=0):
    message = f"{IDs},{COM},{TXT},{colorcode},{locX},{locY},{wide},{tall},{inverter},{rotation}"
    data = list(message.encode('utf-8'))
    i2cbus.write_i2c_block_data(IDs, 0, data)
    #time.sleep(0.5)

#get everything that is pipelined into this driver.
for line in sys.stdin:
    i2ctransmit(i2caddress, "text", line, colorcode, locX, locY, wide, tall, inverter, rotation)
    sys.stdout.write(line)


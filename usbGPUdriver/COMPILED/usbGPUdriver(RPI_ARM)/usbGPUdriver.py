#! /usr/bin/python
import sys
import serial

for line in sys.stdin:
    ser = serial.Serial('/dev/ttyACM0',115200)
    ser.write(bytearray(line,'utf-8'))
    ser.close()
    

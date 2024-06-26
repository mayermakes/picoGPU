simply run:

portable version in ./dist

open python version:

pip install -r requirements.txt

usage in CLI:
yourprogram | pseudoGPUdriver.py [arguments]

arguments:
'-c','--color', choices=['BLACK', 'WHITE', 'BLUE', 'RED' , 'GREEN', 'CYAN', 'MAGENTA', 'YELLOW' ], default= 'BLACK', help= 'choose the background color', 
'-x','--locX',  default= '0', help= 'location in X axis', 
'-y','--locY',  default= '0', help= 'location in Y axis', 
'-w','--wide',  default= '1', help= '(wide) width of text', 
'-t','--tall',  default= '1', help= '(tall) height of text', 
'-i','--invert',  default= '0',choices=[ 0, 1 ], help= 'invert output 0= no, 1= yes', 
'-r','--rotate',  default= '0',choices=[ 0, 1, 2, 3 ], help= 'rotate output', 




or as a module in python;:

import pseudoGPUdriver

i2caddress = 0x05 # default address can be overwritten
line = "whatevery your want to print"
colorcode= BLACK # see choices above
locX= 0 # location of text in X Axis
locY= 0 # location of text in Y Axis
wide = 1 # width of text
tall = 1 # height of text
inverter = 0 # if your text is inverted or not
rotation = 0 # rotation of text

#send to pseudoGpu:

pseudoGPUdriver.i2ctransmit(i2caddress, "text", line, colorcode, locX, locY, wide, tall, inverter, rotation)

#the "text" argument is needed, no graphics modes implemented yet, but this is reserved to enter other modes in the future.

import socket
import struct
import sys
import os
import thread
import time


text = ""

frames = int(sys.argv[1])

os.system("rm -f *.jpg")

images = ""

for n in range(0, frames):

    x = n
    y = n
    z = n

    text += "NAME =  samples/video/img2_"+str(n)+".ppm\n"
    text += "TYPE = PPM\n"
    text += "CODIFICATION = binary\n"

    text += "WIDTH = 500\n"
    text += "HEIGHT = 250\n"

    text += "UPPER_LEFT = 127 179 255    \n"
    text += "LOWER_LEFT = 255 255 255     \n" 
    text += "UPPER_RIGHT = 127 179 255 \n"
    text += "LOWER_RIGHT = 255 255 255 \n"
    text += "\n"
    text += "MIN_DEPHT = 0.001\n"
    text += "MAX_DEPHT = 4\n"
    text += "RAY_SHOTS = 5\n"
    text += "\n"
    text += "THREADS = 10\n"
    text += "\n"
    text += "SHADER = TOON\n"
    text += "\n"
    text += "SPHERE = -1 0 -1 0.5 TOON 0.0 0.3 0.8 ; 0 0 0 ; \n"
    text += "COLORS { \n"
    text += "1.0 0.0 0.0\n"
    text += "0.9 0.0 0.0\n"
    text += "0.8 0.0 0.0\n"
    text += "0.7 0.0 0.0\n"
    text += "0.6 0.0 0.0\n"
    text += "0.5 0.0 0.0\n"
    text += "0.4 0.0 0.0\n"
    text += "0.3 0.0 0.0\n"
    text += "0.2 0.0 0.0\n"
    text += "0.1 0.0 0.0\n"
    text += "}\n"
    text += "\n"
    text += "SPHERE = 0 -100.5 -1 100 TOON 0.0 0.0 0.0 ; 0 0 0; \n"
    text += "COLORS { \n"
    text += "0 1 0\n"
    text += "0 0.9 0\n"
    text += "0 0.8 0\n"
    text += "0 0.7 0\n"
    text += "0 0.6 0\n"
    text += "0 0.5 0\n"
    text += "0 0.4 0\n"
    text += "0 0.3 0\n"
    text += "0 0.2 0\n"
    text += "0 0.1 0\n"
    text += "0 0.0 0\n" 
    text += "}\n"
    text += "\n"
    text += "LIGHT = SPOT ; 1 1 1 ; 2 0 0 ; -1 0 -1 ; "+str(x)+"\n"
    text += "NATURAL_LIGHT = 0.4 0.4 0.4\n"
    text += "\n"
    text += "CAMERA = POSITIONABLE ; 0 0 4 ; 0 0 -1 ; 0 1 0 ; 20 ; 0 ; 0 0 -1\n"


    f = open("samples/video/play.txt","w") #opens file with name of "test.txt"

    f.write(text)


    f.close()

    # os.system("echo "+str(text)+" > samples/video/play.txt")
    time.sleep(1)
    os.system("g++ -std=c++11 -pthread -Wall src/render.cpp -o render && ./render samples/video/play.txt")
    os.system("convert samples/video/img2_"+str(n)+".ppm samples/video/img2_"+str(n)+".jpg")
    images += "samples/video/img2_"+str(n)+".jpg "
    
os.system("rm samples/video/*.txt && rm samples/video/*.ppm")    
os.system("convert -delay 20 -loop 0 "+images+" video2.gif")
    




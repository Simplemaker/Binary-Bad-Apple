'''View an arbitary binary frame'''

from PIL import Image

FRAME = 100

IN_RES = (80, 60)
BUFFER_SIZE = IN_RES[0] * IN_RES[1]

f = open("Bad Apple.bin", "rb")

frame = 0
while(True):
    buffer = f.read(BUFFER_SIZE)
    if frame == FRAME:
        im = Image.frombytes("L", IN_RES, buffer)
        im.show()
    frame+=1

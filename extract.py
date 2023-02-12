'''Binary Video Extractor

Given a video, converts each frame to a BW 80x60 image, and stores the value in a binary file'''

import cv2
from PIL import Image
from pathlib import Path

OUT_RES = (80,24)

def pixel2color(pixel):
    return int(sum(pixel) / 3 / 16)

def arrayToBytes(array):
    nibble = 0
    byte_array = []
    for i in range(0, len(array), 2):
        byte_array.append(array[i] + array[i+1] * 16)
    return bytearray(byte_array)

def writeFrame(file, image):
    pixels = image.load()
    for y in range(image.size[1]):
        colorarray = []
        for x in range(image.size[0]):
            colorarray.append(pixel2color(pixels[x,y]))
        file.write(arrayToBytes(colorarray))

def extractVideo(inpath, outpath, printStatus=False):
    vc = cv2.VideoCapture(inpath.as_posix())
    f = open(outpath, "wb")
    count = 0
    while True:
        success,image = vc.read()
        if not success:
            break
        if printStatus:
            print(f'captured image {count}')
        image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        im_pil = Image.fromarray(image)
        im_pil = im_pil.resize(OUT_RES)
        writeFrame(f, im_pil)
        count += 1
    f.close()

extractVideo(Path("Bad Apple.webm"), Path("Bad Apple.bin"), printStatus=True)

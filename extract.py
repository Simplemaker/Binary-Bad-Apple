'''Binary Video Extractor

Given a video, converts each frame to a BW 80x60 image, and stores the value in a binary file'''

import cv2
from PIL import Image
from pathlib import Path

OUT_RES = (80,24)
## necessary for png extraction
FRAMES = 6572


def pixel2color(pixel):
    '''Converts a RGB pixel to a 4 bit grayscale value'''
    return int(sum(pixel) / 3 / 16)

def writeFrame(file, image):
    pixels = image.load()
    for y in range(image.size[1]):
        colorarray = []
        for x in range(image.size[0]):
            colorarray.append(pixel2color(pixels[x,y]))
        file.write(bytearray(colorarray))

def extractVideo(inpath, callback, printStatus=False):
    vc = cv2.VideoCapture(inpath.as_posix())
    
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
        callback(im_pil)
        count += 1
    

def binaryBadApple():
    f = open(Path("Bad Apple.bin"), "wb")
    extractVideo(Path("Bad Apple.webm"), lambda im : writeFrame(f, im) , printStatus=True)
    f.close()

binaryBadApple()

def pngBadApple():
    im = Image.new(mode="L", size=(OUT_RES[0], OUT_RES[1]*FRAMES))
    currentFrame = 0
    def callback(im2):
        nonlocal currentFrame
        Image.Image.paste(im, im2, (0, currentFrame * OUT_RES[1]))
        currentFrame += 1
    extractVideo(Path("Bad Apple.webm"), callback, printStatus=True)
    im.save("Bad Apple.png")

# pngBadApple()

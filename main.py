from cairosvg import svg2png
import os
import moviepy.video.io.ImageSequenceClip

image_folder = 'png_files/Donut'
max = 86

def makeVideo():
    print("Making video...")
    fps=30
    image_files = []

    for rep in range(0,3):
        for i in range(0,max):
            path = (image_folder+"/output"+str(i)+".png")
            image_files.append(path)

    clip = moviepy.video.io.ImageSequenceClip.ImageSequenceClip(image_files, fps=fps)
    clip.write_videofile('my_video.mp4')

    for i in range(0,0):
        os.remove(image_folder+"/output"+str(i)+".png")

import os

def makePNG():

    for i in range(0,max):
        svg_code = open("video/Donut/outdraw"+str(i)+".svg").read()
        try:
            svg2png(bytestring=svg_code,write_to=(image_folder+'/output'+str(i)+'.png'), background_color="gray")
        except:
            print("Wrong file structure, Picture #"+str(i))
        else:
            print("Picture #"+str(i)+"done")
            print("["+(i+1)*"+"+(max-i-1)*"."+"]")

    for i in range(0,0):
        os.remove("video/Donut/outdraw"+str(i)+".svg")
    


_, _, files = next(os.walk("video/Donut"))
max = len(files)
makePNG()
makeVideo()
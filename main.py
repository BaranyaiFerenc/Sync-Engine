from cairosvg import svg2png
import os
import moviepy.video.io.ImageSequenceClip

image_folder = 'png_files/Cube'
max = 360

def makeVideo():
    print("Making video...")
    fps=30
    image_files = []

    for i in range(0,max):
        path = (image_folder+"/output"+str(i)+".png")
        image_files.append(path)

    clip = moviepy.video.io.ImageSequenceClip.ImageSequenceClip(image_files, fps=fps)
    clip.write_videofile('my_video.mp4')


for i in range(0,max):
    svg_code = open("video/Cube/outdraw"+str(i)+".svg").read()
    svg2png(bytestring=svg_code,write_to=(image_folder+'/output'+str(i)+'.png'), background_color="white")
    print("Picture #"+str(i)+"done")
    print("["+(i+1)*"+"+(max-i-1)*"."+"]")

makeVideo()
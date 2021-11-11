import cv2
#import numpy as np 




while True:
    #This is to check whether to break the first loop
    isclosed=0
    cap = cv2.VideoCapture('C:/Users/liors/Documents/Blender Projects/Butterfly Knife Wallpaper/animation/wallpaper.mp4')
    while (True):
        ret, frame = cap.read()
        # It should only show the frame when the ret is true
        if ret == True:
            print(frame)
            cv2.imshow('frame',frame)
            if cv2.waitKey(1) == 27:
                # When esc is pressed isclosed is 1
                isclosed=1
                break
        else:
            break
    # To break the loop if it is closed manually
    if isclosed:
        break



cap.release()
cv2.destroyAllWindows()
"""
import cv2
from os import walk

filenames = next(walk("C:/Users/liors/Documents/Blender Projects/Butterfly Knife Wallpaper/animation/animation PNG"), (None, None, []))[2]  # [] if no file
frames = []

while (True):
    # It should only show the frame when the ret is true
    for i in filenames:
        img = cv2.imread("C:/Users/liors/Documents/Blender Projects/Butterfly Knife Wallpaper/animation/animation PNG/"+i)
        print(img)
        cv2.imshow('frame', img)
        if cv2.waitKey(1) == 27:
            # When esc is pressed isclosed is 1
            isclosed=1
            break
        else:
            break





cap.release()
cv2.destroyAllWindows()
"""

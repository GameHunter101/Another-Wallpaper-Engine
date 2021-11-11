import sys, os
import shutil
from shutil import copyfile
import pathlib




if __name__ == "__main__":
    filename = str(pathlib.Path().resolve())
    filename += "\\dependancies\\"
    print(filename)
    """dirname = os.path.dirname(__file__)
    filename = os.path.join(dirname, 'dependancies\\')
    orig_path = os.environ.get("AppData") + "\\Microsoft\\Windows\\Themes\\TranscodedWallpaper"
    dest_path = os.environ.get("AppData") + "\\Microsoft\\Windows\\Themes\\temp_wp.png"
    shutil.copy2(orig_path, dest_path)

    f = open(filename +"temp.txt", "w+")
    f = open("temp.txt", "w+")
    f.write(filename)
    f.close()"""

    print(filename)
    copyfile("wallpaper.mp4", filename+"video_looper-win32-x64\\resources\\app\\wallpaper.mp4")
    os.startfile(filename + "video_looper-win32-x64\\video_looper.exe")
    os.startfile(filename +"Another Wallpaper Engine.exe")

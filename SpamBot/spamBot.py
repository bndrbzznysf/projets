import pyautogui as auto
import time
import webbrowser

import os

path = "C:\\Users\\Ce PC\\Desktop\\Projects\\Python"
os.chdir(path)

def sendSpam():
    words = open('spam.txt', 'r')
    #webbrowser.open('https://web.whatsapp.com/')
    time.sleep(10)
    for word in words:
        auto.typewrite(word)
        auto.press('enter')

sendSpam()
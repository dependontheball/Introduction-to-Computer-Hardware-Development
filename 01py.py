from machine import Pin
from time import sleep
red = Pin(40, Pin.OUT)
yellow = Pin(41, Pin.OUT)
green = Pin(42, Pin.OUT)
sw = Pin(2, Pin.IN, Pin.PULL_UP)
red.value(0)
yellow.value(0)
green.value(0) 
 
count = 0
first = 0
 

while True:
    if sw.value() == 0: # สวิตช์ถูกกด
        while(sw.value() == 0):
            if first == 0:
                count += 1
                first += 1
            if count%3 == 0:
                red.value(0)
                yellow.value(0)
                green.value(1)
            if count%3 == 1:
                red.value(0)
                yellow.value(1)
                green.value(0)
            if count%3 == 2:
                red.value(1)
                yellow.value(0)
                green.value(0)
        print(f"{count}")
        sleep(0.03)

    else: # สวิตช์ถูกปล่อย
        first = 0
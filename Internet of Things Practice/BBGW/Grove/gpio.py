import mraa
import time
#mraa.gpio60 = P9_14 = GPIO_50
led = mraa.Gpio(60)
led.dir(mraa.DIR_OUT)

while True:
    led.write(1)
    time.sleep(1)
    led.write(0)
    time.sleep(1)


import mraa
import time
#mraa.aio1 = AIN0
rotary = mraa.Aio(1)

while True:
    print(rotary.read())
    time.sleep(1)


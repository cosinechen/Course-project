import time
from logo import print_seeedstudio
import Adafruit_BBIO.GPIO as GPIO

# Note: Use P9_22(UART2_RXD) as GPIO.
# Connect the Grove Button to UART Grove port of Beaglebone Green.
Button = "P9_22"            # GPIO P9_22
GPIO.setup(Button, GPIO.IN)

if __name__== '__main__':
    print_seeedstudio()

    while True:
        if GPIO.input(Button):
            print "Button is pressed."
            time.sleep(1)
        else:
            print "Button is unstuck."
            time.sleep(1)
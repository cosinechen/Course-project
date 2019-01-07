import time
from logo import print_seeedstudio
import Adafruit_BBIO.GPIO as GPIO

# Note: Use P9_22(UART2_RXD) as GPIO.
# Connect the Grove Relay to UART Grove port of Beaglebone Green.
RELAY = "P9_22"            # GPIO P9_22
GPIO.setup(RELAY, GPIO.OUT)

if __name__== '__main__':
    print_seeedstudio()

    while True:
        try:
            # input
            input = raw_input('Please input on or off:')

            if input == 'on':
                print "switch on RELAY"
                # Send HIGH to switch on RELAY
                GPIO.output(RELAY, GPIO.HIGH)
            elif input == 'off':
                print "switch off RELAY"
                # Send LOW to switch off RELAY
                GPIO.output(RELAY, GPIO.LOW)
            else:
                print "Invalid input! Please input on or off."
            
        except KeyboardInterrupt:
            GPIO.output(RELAY, GPIO.LOW)
            break

        except IOError:
            print "Error"
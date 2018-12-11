import sys
from time import sleep
import urllib2

a = 0
b = 1
c = 0
baseURL = "https://api.thingspeak.com/update?api_key=3NR0GTMVEM2R36XX&field1="
while(a < 1000):
        adc = open("/sys/bus/iio/devices/iio:device0/in_voltage0_raw", "r")
        value = (adc.read(5)).strip()
        print value
        f = urllib2.urlopen(baseURL +str(value))
        f.read()
        f.close()
        adc.close()
        sleep(5)

print "Program has ended"
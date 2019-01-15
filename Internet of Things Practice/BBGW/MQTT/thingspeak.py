import sys
from time import sleep
import urllib2

a = 0
b = 1
c = 0
baseURL = "http://api.thingspeak.com/update?api_key=LOC0WSN4TJY9W5O0&field1="
while(a < 1000):
	print a
	f = urllib2.urlopen(baseURL +str(a))
	f.read()
	f.close()
	sleep(5)
	c = a
	a = a + b
	b = c 	
print "Program has ended"
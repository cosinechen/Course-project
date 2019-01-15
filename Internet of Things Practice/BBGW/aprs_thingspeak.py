from __future__ import print_function
import paho.mqtt.publish as publish
import psutil
'''uart'''
import Adafruit_BBIO.UART as UART
import serial
import time
import re

name = [
	"windSpeed",
	"temperature",
	"rainfall"
]

channelID = "674893"

apiKey = "XAJA1U9574PKA6O9"

useUnsecuredTCP = False

useUnsecuredWebsockets = False

useSSLWebsockets = True

mqttHost = "mqtt.thingspeak.com"

# Set up the connection parameters based on the connection type
if useUnsecuredTCP:
    tTransport = "tcp"
    tPort = 1883
    tTLS = None

if useUnsecuredWebsockets:
    tTransport = "websockets"
    tPort = 80
    tTLS = None

if useSSLWebsockets:
    import ssl
    tTransport = "websockets"
    tTLS = {'ca_certs':"/etc/ssl/certs/ca-certificates.crt",'tls_version':ssl.PROTOCOL_TLSv1}
    tPort = 443

# Create the topic string
topic = "channels/" + channelID + "/publish/" + apiKey

#print value
ser1 = serial.Serial(port = "/dev/ttyO1", baudrate = 2400)
ser1.close()
while(True):
	adc = open("/sys/bus/iio/devices/iio:device0/in_voltage1_raw", "r")
	soilmoisture = (adc.read(5)).strip()
	
	ser1.open()
	if ser1.isOpen():
		while True:
			x = ser1.readline()
			#print len(x)
			if len(x) < 38 or len(x) > 38:
				continue
			elif str(x[0])!= "c":
				continue
			else:
				break
	ser1.close()
	
	'''x==string'''
	#print(len(x))
	print(str(x))
	cut = re.split('c|s|g|t|r|p|h|b|\*',str(x))
	cut.pop()
	cut.pop(0)
	print(cut)
	[float(_) for _ in cut]
	wind = cut[1] = int(cut[1])*1609.344/3600
	temp = cut[3] = (int(cut[3])-32)*5/9
	rain = cut[4] = int(cut[4])*25.4
	print(str(name[0])+" : "+str(wind)+ "m/s")
	print(str(name[1])+" : "+str(temp)+ "^C")
	print(str(name[2])+" : "+str(rain)+ "mm")
	''''''
	'''code[2]'''
	if wind <= 0.2 and wind >= 0.0:
		print("0 grade, Calm")
	elif wind <= 1.5 and wind >= 0.3:
		print("1 grade, Light air")
	elif wind <= 3.3 and wind >= 1.6:
		print("2 grade, Light breeze")
	elif wind <=5.4 and wind >=3.4:
		print("3 grade, Gentle breeze")
	elif wind <=7.9 and wind >=5.5:
		print("4 grade, Moderate breeze")
	else:
		print("5 grade or more, Fresh breeze")

	if rain < 2 and rain >= 0.0:
		print("No rain")
	elif rain <25 and rain >= 2:
		print("Drizzle")
	elif rain <50 and rain >= 25:
		print("Sprinkle")
	elif rain < 80 and rain >= 50:
		print("Rain")
	elif rain <200 and rain >=80:
		print("Heavy rain")
	elif rain <350 and rain >=200:
		print("Extremely heavy rain")
	elif rain <500 and rain >=350:
		print("Torrential rain")
	else:
		print("Extremely torrential rain")

	'''code[2]'''
	print("Soil moisture = ",soilmoisture)
	print("wind = ",wind," m/s temp = ",temp," ^C rain = ",rain," mm/h")
	print("\n")
	# build the payload string
	tPayload = "field1="+soilmoisture+"&field2="+str(wind)+"&field3="+str(temp)+"&field4="+str(rain)


	# attempt to publish this data to the topic 
	try:
		publish.single(topic, payload=tPayload, hostname=mqttHost, port=tPort, tls=tTLS, transport=tTransport)

	except (KeyboardInterrupt):
		break

	except:
		print ("There was an error while publishing the data.")

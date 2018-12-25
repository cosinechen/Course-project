import mraa
import time
#mraa.gpio60 = P9_14 = GPIO_50
#mraa.gpio62 = P9_16 = GPIO_51
gpio_1 = mraa.Gpio(60)
gpio_2 = mraa.Gpio(62)
# set gpio 60 and gpio 62 to output
gpio_1.dir(mraa.DIR_OUT)
gpio_2.dir(mraa.DIR_OUT)
# toggle both gpio's
while True:
    gpio_1.write(1)
    gpio_2.write(0)
    time.sleep(1)
    gpio_1.write(0)
    gpio_2.write(1)
    time.sleep(1)


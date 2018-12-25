import mraa
import time
# initialise PWM
x = mraa.Pwm(60)
# set PWM period
x.period_us(700)
# enable PWM
x.enable(True)
value= 0.0
while True:
    # write PWM value
    x.write(value)
    time.sleep(0.5)
    value = value + 0.1
    if value >= 1:
        value = 0.0


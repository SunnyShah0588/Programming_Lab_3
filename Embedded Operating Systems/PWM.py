
import Adafruit_BBIO.GPIO as GPIO
import Adafruit_BBIO.PWM as PWM
import time

GPIO.setup("P8_7",GPIO.IN)
GPIO.setup("P8_8",GPIO.IN)
GPIO.setup("P8_9",GPIO.IN)
GPIO.setup("P8_10",GPIO.IN)

#PWM.start(channel, duty, freq=2000, polarity=0)
PWM.start("P8_13")

''' Frequency: This defines how many full on/off "cycles" are generated in a second
Period: This defines how long one complete pulse cycle takes
Duty cycle: This specifies the time the signal is high during one full period

When you initialize a PWM, you can initialize it with two to four parameters listed as follows:

Channel (header pin)
Duty (as in percent, 0-100)
Frequency (periods in a second, default is 2000)
And polarity (0 or 1. With this you can invert the duty cycle, default is 0)
 '''
#optionally, you can set the frequency as well as the polarity from their defaults: 
#PWM.start("P8_13", 50, 1000, 1) ##50% duty and 100hz cycle
#The valid values for duty are 0.0 to 100.0.
# The start method activate pwm on that channel.
# There is no need to setup the channels with Adafruit_BBIO.PWM.
#You can also set the frequency
#PWM.set_frequency("P9_14", 10)

while True:
	if (GPIO.input("P8_8")==0):
		PWM.set_duty_cycle("P8_13", 20)		#SLOW
	elif (GPIO.input("P8_7")==0):
		PWM.set_duty_cycle("P8_13", 90)		#FAST
	elif (GPIO.input("P8_10")==0):
		PWM.set_duty_cycle("P8_13", 50)		#MEDIUM
	elif (GPIO.input("P8_9")==0):
		PWM.set_duty_cycle("P8_13", 0)		#OFF

PWM.stop("P8_13") 
PWM.cleanup()




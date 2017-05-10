import Adafruit_BBIO.GPIO as GPIO
import time

led_pins = ['P9_23', 'P9_24', 'P9_11', 'P9_12', 'P9_13', 'P9_14', 'P9_15', 'P9_16']
seg = ['P8_11', 'P8_12', 'P8_13', 'P8_14', 'P8_15', 'P8_16', 'P8_17', 'P8_18']
switch = ['P8_7', 'P8_8', 'P8_9', 'P8_10']

zero = ['P8_11', 'P8_12', 'P8_13', 'P8_14', 'P8_15', 'P8_16']
one = ['P8_12', 'P8_13']
two = ['P8_11', 'P8_12', 'P8_14', 'P8_15', 'P8_17']
three = ['P8_11', 'P8_12', 'P8_13', 'P8_14', 'P8_17']

for i in range(len(led_pins)):
	GPIO.setup(led_pins[i], GPIO.OUT)
	GPIO.setup(seg[i], GPIO.OUT)

for j in range(len(switch)):
	GPIO.setup(switch[j], GPIO.IN) 

def led_clear():
	for i in range(len(led_pins)):
		GPIO.output(led_pins[i], GPIO.LOW)

def seg_clear():
	for i in range(len(seg)):
		GPIO.output(seg[i], GPIO.HIGH)

def seg_disp(b):
	if b == 0:
		seg_clear()
		for i in range(len(zero)):
			GPIO.output(zero[i], GPIO.LOW)
	if b == 1:
		seg_clear()
		for j in range(len(one)):
			GPIO.output(one[j], GPIO.LOW)
	if b == 2:
		seg_clear()
		for k in range(len(two)):
			GPIO.output(two[k], GPIO.LOW)
	if b == 3:
		seg_clear()
		for l in range(len(three)):
			GPIO.output(three[l], GPIO.LOW)
			
def ledUp(current):
	if current == 0:
		led_clear()
		GPIO.output("P9_23",GPIO.HIGH)
	elif current == 1:
		led_clear()
		GPIO.output("P9_16",GPIO.HIGH)
	elif current == 2:
		led_clear()
		GPIO.output("P9_14",GPIO.HIGH)
	elif current == 3:
		led_clear()
		GPIO.output("P9_12",GPIO.HIGH)
		
def ledDown(current):
	if current == 0:
		led_clear()
		GPIO.output("P9_24",GPIO.HIGH)
	elif current == 1:
		led_clear()
		GPIO.output("P9_15",GPIO.HIGH)
	elif current == 2:
		led_clear()
		GPIO.output("P9_13",GPIO.HIGH)
	elif current == 3:
		led_clear()
		GPIO.output("P9_11",GPIO.HIGH)	

currentLevel = 0
goToLevel = 0
seg_disp(0)
led_clear()
while True:
	if (GPIO.input("P8_10") == 0):#0
		print 'Button 0'
		goToLevel = 0
		if (currentLevel > goToLevel):
			while (currentLevel >= goToLevel):
				seg_disp(currentLevel)
				ledDown(currentLevel)
				time.sleep(1)
				currentLevel -= 1
			currentLevel += 1
	elif (GPIO.input("P8_8") == 0):#1
		print 'Button 1'
		goToLevel = 1
		if (currentLevel < goToLevel):
			while (currentLevel <= goToLevel):
				seg_disp(currentLevel)
				ledUp(currentLevel)
				time.sleep(1)
				currentLevel += 1
			currentLevel -= 1
		elif (currentLevel > goToLevel):
			while (currentLevel >= goToLevel):
				seg_disp(currentLevel)
				ledDown(currentLevel)
				time.sleep(1)
				currentLevel -= 1
			currentLevel += 1
	elif (GPIO.input("P8_9") == 0):#2
		print 'Button 2'
		goToLevel = 2
		if (currentLevel < goToLevel):
			while (currentLevel <= goToLevel):
				seg_disp(currentLevel)
				ledUp(currentLevel)
				time.sleep(1)
				currentLevel += 1
			currentLevel -= 1
		elif (currentLevel > goToLevel):
			while (currentLevel >= goToLevel):
				seg_disp(currentLevel)
				ledDown(currentLevel)
				time.sleep(1)
				currentLevel -= 1
			currentLevel += 1
	elif (GPIO.input("P8_7") == 0):#3
		print 'Button 3'
		goToLevel = 3
		if (currentLevel < goToLevel):
			while (currentLevel <= goToLevel):
				seg_disp(currentLevel)
				ledUp(currentLevel)
				time.sleep(1)
				currentLevel += 1
			currentLevel -= 1

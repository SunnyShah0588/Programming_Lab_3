import Adafruit_BBIO.GPIO as GPIO
import time

GPIO.setup("P8_11",GPIO.OUT)            #C Red
GPIO.setup("P8_12",GPIO.OUT)            #D Green
GPIO.setup("P8_13",GPIO.OUT)            #C Yellow
GPIO.setup("P8_14",GPIO.OUT)            #D Green
GPIO.setup("P8_15",GPIO.OUT)            #C Green
GPIO.setup("P8_16",GPIO.OUT)            #D Yellow
GPIO.setup("P8_17",GPIO.OUT)            #C Green
GPIO.setup("P8_18",GPIO.OUT)            #D Red

GPIO.setup("P9_11",GPIO.OUT)            #B Red
GPIO.setup("P9_12",GPIO.OUT)            #A Green
GPIO.setup("P9_13",GPIO.OUT)            #B Yellow
GPIO.setup("P9_14",GPIO.OUT)            #A Green
GPIO.setup("P9_15",GPIO.OUT)            #B Green
GPIO.setup("P9_16",GPIO.OUT)            #A Yellow
GPIO.setup("P9_23",GPIO.OUT)            #A Red
GPIO.setup("P9_24",GPIO.OUT)            #B Green

while True:
        num=0
        GPIO.output("P9_23",GPIO.HIGH)  #A Red
        GPIO.output("P8_11",GPIO.HIGH)  #C Red
        GPIO.output("P9_11",GPIO.LOW)           #B Red
        GPIO.output("P8_18",GPIO.LOW)           #D Red
        
        GPIO.output("P9_15",GPIO.HIGH)  #B Green        
        GPIO.output("P9_24",GPIO.HIGH)  #B Green
        GPIO.output("P8_14",GPIO.HIGH)  #D Green
        GPIO.output("P8_12",GPIO.HIGH)  #D Green
        
        time.sleep(8)
        
        while num < 5:

                GPIO.output("P9_15",GPIO.LOW)           #B Green
                GPIO.output("P9_24",GPIO.LOW)           #B Green
                GPIO.output("P8_14",GPIO.LOW)           #D Green
                GPIO.output("P8_12",GPIO.LOW)           #D Green
                GPIO.output("P9_16",GPIO.LOW)           #A Yellow
                GPIO.output("P8_13",GPIO.LOW)           #C Yellow

                GPIO.output("P9_13",GPIO.HIGH)  #B Yellow       
                GPIO.output("P8_16",GPIO.HIGH)  #D Yellow
                time.sleep(1)
                GPIO.output("P9_13",GPIO.LOW)           #B Yellow
                GPIO.output("P8_16",GPIO.LOW)           #D Yellow
                
                time.sleep(1)
                num=num+1

        num=0
        GPIO.output("P9_23",GPIO.LOW)           #A Red 
        GPIO.output("P8_11",GPIO.LOW)           #C Red
        GPIO.output("P9_11",GPIO.HIGH)  #B Red
        GPIO.output("P8_18",GPIO.HIGH)  #D Red
                
        GPIO.output("P9_12",GPIO.HIGH)  #A Green
        GPIO.output("P9_14",GPIO.HIGH)  #A Green
        GPIO.output("P8_17",GPIO.HIGH)  #C Green
        GPIO.output("P8_15",GPIO.HIGH)  #C Green
                
        time.sleep(8)

        while num < 5:
                        GPIO.output("P9_12",GPIO.LOW)           #A Green
                        GPIO.output("P9_14",GPIO.LOW)           #A Green
                        GPIO.output("P8_17",GPIO.LOW)           #C Green
                        GPIO.output("P8_15",GPIO.LOW)           #C Green
                        GPIO.output("P9_11",GPIO.HIGH)  #B Red
                        GPIO.output("P8_18",GPIO.HIGH)  #D Red

                        GPIO.output("P9_16",GPIO.HIGH)  #A Yellow
                        GPIO.output("P8_13",GPIO.HIGH)  #C Yellow
                        time.sleep(1)
                        GPIO.output("P9_16",GPIO.LOW)           #A Yellow
                        GPIO.output("P8_13",GPIO.LOW)           #C Yellow
                        time.sleep(1)
                        num=num+1

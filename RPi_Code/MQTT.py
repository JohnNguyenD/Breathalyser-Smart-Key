import paho.mqtt.publish as publish
import RPi.GPIO as GPIO
import time

button = 4

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(button, GPIO.IN, pull_up_down = GPIO.PUD_DOWN)

while True:
    if GPIO.input(button) == GPIO.HIGH:
        print("Sending 1..")
        publish.single("Testing", "1", hostname = "192.168.0.15") #hostname is your RPi ip
        time.sleep(2)
    elif GPIO.input(button) == GPIO.LOW:
        print("Sending 0..")
        publish.single("Testing", "0", hostname = "192.168.0.15")
        time.sleep(2)

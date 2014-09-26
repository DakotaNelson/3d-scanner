"""
arduino.py
-------
Author: vascop (GitHub)
Adapted by: Nick Francisci and Lindsey Vanderlyn
Status: Complete & Tested
Description: An interface class to wrap the Arduino serial interface

"""

import time
import serial
import sys


class Arduino(object):

    __OUTPUT_PINS = -1

    def __init__(self, port=None, baudrate=115200):
        if not port:
            if sys.platform.startswith('win'):
                port = "COM4"
            elif sys.platform.startswith('lin'):
                port = "/dev/ttyACM0"
            else:
                print("ERROR: unsupported OS!")

        self.serial = serial.Serial(port, baudrate)
        self.serial.write('99')

    def __str__(self):
        return "Arduino is on port %s at %d baudrate" % (self.serial.port,
                                                         self.serial.baudrate)

    def output(self, pinArray):
        self.__sendData(len(pinArray))

        if(isinstance(pinArray, list) or isinstance(pinArray, tuple)):
            self.__OUTPUT_PINS = pinArray
            for each_pin in pinArray:
                self.__sendData(each_pin)
        return True

    def setLow(self, pin):
        # sets specified pin to LOW
        self.__sendData('0')
        self.__sendData(pin)
        return True

    def setHigh(self, pin):
        #sets specified pin to HIGH
        self.__sendData('1')
        self.__sendData(pin)
        return True

    def getState(self, pin):
        #reads pin state of specified pin state
        self.__sendData('2')
        self.__sendData(pin)
        return self.__formatPinState(self.__getData()[0])

    def analogWrite(self, pin, value):
        #Set analog value of specified pin
        self.__sendData('3')
        self.__sendData(pin)
        self.__sendData(value)
        return True

    def analogRead(self, pin):
        #reads analog pin state of specified pin
        self.__sendData('4')
        self.__sendData(pin)
        return self.__getData()
    
    def pwmWrite(self, pin, value):
        #sets pwm duty cycle for specified pin
        self.__sendData('5')
        self.__sendData(pin)
        self.__sendData(value)
        return True

    def turnOff(self):
        #sets all pins on arduino low
        for each_pin in self.__OUTPUT_PINS:
            self.setLow(each_pin)
        return True

    def __sendData(self, serial_data):
        while(self.__getData()[0] != "w"):
            pass
        self.serial.write(str(serial_data))

    def __getData(self):
        return self.serial.readline().rstrip('\n')

    def __formatPinState(self, pinValue):
        if pinValue == '1':
            return True
        else:
            return False

    def __exit__(self, type, value, tb):
        self.turnOff()
        self.close()

    def close(self):
        self.serial.close()
        return True


if __name__ == '__main__':
    a = Arduino()
    a.output([4])
    time.sleep(0.1)
    a.setHigh(4)
    #a.analogWrite(14,255)
    time.sleep(30)
    a.setLow(4)

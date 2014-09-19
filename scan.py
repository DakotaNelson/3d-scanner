""" Code to collect 3d scan data"""

import pyplot.matplotlib as plt 
import arduino as a
import serial
import sys
import time


def capture_data(resolution, arduino = serial.Serial("/dev/ttyACM0", 115200)):
    """
    Function collects x and y servo position data and sensor output from arduino
    inputs:
        resolution -> number of steps taken between readings
        arduino -> serial device being written/readings
    outputs:
        coordinates -> unprocessed list of points 
    """
    #tells arduino the step size
    arduino.write(resolution)
    coordinates = []

    #sets the number of expected points (so the loop will know when to exit)
    totalPoints = (64/resolution)**2

    while len(coordinates < totalPoints):
        data = arduino.readline().rstrip('\n')
        coordinates.append(data)
    return coordinates

def processData(rawData):
    """
    Does math to turn sensor and servo values into physical distances

    Inputs:
        rawData -> list of 3 value coordinate pairs
    Outputs:
        processedData -> list of real world coordinates in units
    """

    


#function to scan one column

#function to rotate 1 row

if __name__ == '__main__':
    s = Scanner(3)
    s.tilt(100)
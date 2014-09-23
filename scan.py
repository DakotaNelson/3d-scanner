""" Code to collect 3d scan data"""

import pyplot.matplotlib as plt 
import arduino as a
import serial
import sys
import time
import numpy as np 


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
        #While we don't have all the data yet,
        #read it from the serial and append to a list
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
    x = []
    y =  []
    z = []
    #Assuming origin is at motor when at center of pan and tilt

    callibration = 0 #Fill in with acutal callibration value
    for coordinate in rawData:
        distance = coordinate[2] * callibration
        z.append(distance)

        #deals with conversion between servo value and angle
        angle_conversion = (np.py/4)/128
        #converts to cartesian shifting origin to center servo value
        horizontal_coordinate = distance*np.cos((64-x)*angle_conversion)
        #converts to cartesian leaving origin at base for y
        vertical_coordinate = distance*np.sin((y)*angle_conversion)

    


#function to scan one column

#function to rotate 1 row

if __name__ == '__main__':
    s = Scanner(3)
    s.tilt(100)
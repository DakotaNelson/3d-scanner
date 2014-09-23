""" Code to collect 3d scan data"""

from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
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
    arduino.write(str(resolution))
    coordinates = []

    #sets the number of expected points (so the loop will know when to exit)
    totalPoints = (128*3/resolution)**2

    while len(coordinates) < 10: #totalPoints):
        #read data from the serial 
        data = arduino.readline().rstrip('\n')
        coordinates.append(data)
    return coordinates

def processData(raw_data):
    """
    Does math to turn sensor and servo values into physical distances

    Inputs:
        rawData -> list of coordinate values, every three make one 
                   coordinate set 
    Outputs:
        processedData -> list of real world coordinates in units
    """
    #Assuming origin is at motor when at center of pan and tilt

    callibration = 0 #Fill in with acutal callibration value
    for index in range(len(raw_data)):
        depth = raw_data[index] * callibration

        #deals with conversion between servo value and angle
        angle_conversion = (np.py/4)/128

        #converts to cartesian shifting origin to center servo value
        horizontal_coordinate = depth*np.cos((96-raw_data[1+index])*angle_conversion)

        #converts to cartesian leaving origin at base for y
        vertical_coordinate = depth*np.sin(96 -(raw_data[2+index])*angle_conversion)
        x.append(horizontal_coordinate)
        y.append(vertical_coordinate)
        z.append(depth)
    return x,y,z

    


#function to scan one column

#function to rotate 1 row

if __name__ == '__main__':
    raw = capture_data(1)
    print raw 
    x,y,z = processedData(raw)
    print x
    # fig = plt.figure()
    # Axes3D.scatter(X,Y, Z)
    # plt.show()
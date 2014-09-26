#include <Servo.h>

Servo pan_servo;
Servo tilt_servo;

const int SERIAL_RATE = 9600;
const int STEP = 3; // move one degree between scans

const int PAN_PIN = 3;
const int TILT_PIN = 10;
const int SENSOR = A0;

/////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(SERIAL_RATE);
  pan_servo.attach(PAN_PIN);
  tilt_servo.attach(TILT_PIN);
  pan(0);
  tilt(0);
}

void scan(int resolution){
  int column = -30; // current state of the pan servo
  double val; // distance sensor result stored here

  pan(column);
  tilt(0); // set initial position of servos

  // do all the scanning
  while(column < 30) {

    //scan direction 1
    for(float d1 = -10; d1 < 30; d1 += STEP){
      tilt(d1); //scans one direction horizontally
      val = getDistance();
      
      Serial.print(d1);
      Serial.print(",");
      Serial.print(column);
      Serial.print(",");
      Serial.println(val);
      delay(50);
    }
    column += STEP;
    pan(column);   //move over one step
    delay(50);

    //scans in the other direction
    for(int d2 = 30; d2 > -10; d2 -= STEP){ 
      tilt(d2);
      val = getDistance();
      
      Serial.print(d2);
      Serial.print(",");
      Serial.print(column);
      Serial.print(",");
      Serial.println(val);
      delay(50);
    }
    column += STEP;
    pan(column);
    delay(50);
  } // end scanning loop
  
    pan(0); // reset to pointing straight ahead
    tilt(0); // (mostly for show)
}

void loop() {
  establishContact(); // wait until a keypress comes across the line
  while (Serial.available() > 0) 
  {
    // empty the serial buffer
    char inByte = Serial.read();
  }
  // begin the scan
  scan(10);
}
/////////////////////////////////////////////////////////////////////////////////////////

bool pan(int deg) {
  // deg as in degrees
  // Pan to the correct angle - include calibration
    
  if(deg < -30 || deg > 30) {
    // outside of bounds
    return false;
  }

  deg += 43; // take calibration into account
  pan_servo.write(deg);

  return true; // if successful
}

bool tilt(int deg) {
  // Tilt to the correct angle - include calibration
  
  if(deg < -10 || deg > 90) {
    // outside of bounds
    return false;
  }
  
  deg = -deg;
  deg += 157; // take calibration into account
  tilt_servo.write(deg);

  return true; // if successful
}

void establishContact() {
  while (Serial.available() <= 0) {
    delay(500);
  }
}

double getDistance() {
  double distance;
  distance = analogRead(SENSOR);
  
  // fit on the calibration data (calculated in Matlab)
  // y = p1*x^4 + p2*x^3 + p3*x^2 + p4*x + p5 

  //  Coefficients:
  //    p1 = 1.7565e-09
  //    p2 = -3.1001e-06
  //    p3 = 0.0020337
  //    p4 = -0.62428
  //    p5 = 89.447
  
  distance = 1.7565e-09 * pow(distance,4) + -3.1001e-06 * pow(distance,3) + 0.0020337 * pow(distance,2) + -0.62428 * distance + 89.447;
  
  // returns distance in inches
  return distance;
}

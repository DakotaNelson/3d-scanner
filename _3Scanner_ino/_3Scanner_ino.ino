#include <Servo.h>

Servo pan_servo;
Servo tilt_servo;

const int SERIAL_RATE = 9600;
const int STEP = 3; // move one degree between scans

const int PAN_PIN = 3;
const int TILT_PIN = 10;
const int SENSOR = A0;


String inString = "";    // string to hold input

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(SERIAL_RATE);
  pan_servo.attach(PAN_PIN);
  tilt_servo.attach(TILT_PIN);
}

void scan(int resolution){
  int column = 45; // current state of the pan servo
  int val; // to be returned

  pan(column);
  tilt(90); // set initial position of servos

  // do all the scanning
  while(column < 135) {

    //scan direction 1
    for(float d1 = 90; d1 < 135; d1 += STEP){
      tilt(d1); //scans one direction horizontally
      val = analogRead(SENSOR);
      Serial.println(val);
      Serial.println(d1);
      Serial.println(column);
      delay(100);
    }
    column += STEP;
    pan(column);   //move over one step
    delay(20);

    //scans in the other direction
    for(int d2 = 135; d2 > 90; d2 -= STEP){ 
      tilt(d2);
      val = analogRead(SENSOR);
      Serial.println(val);
      Serial.println(d2);
      Serial.println(column);
      delay(20);
    }
    column += STEP;
    pan(column);
    delay(20);   
  } // end scanning loop
}

void loop() {
  // Read serial input:
  //  while (Serial.available() > 0) {
  //    int inChar = Serial.read();
  //    if (isDigit(inChar)) {
  //      // convert the incoming byte to a char 
  //      // and add it to the string:
  //      inString += (char)inChar; 
  //    }
  //    // if you get a newline, print the string,
  //    // then the string's value:
  //    if (inChar == '\n') {
  //      //Serial.println(inString.toInt());
  //    //resolution is the value sent over serial
  //      scan(inString.toInt());
  //    }
  // }
    scan(10);
    while(true){}
}

bool pan(int deg) {
  // deg as in degrees
  // Pan to the correct angle - include calibration

  pan_servo.write(deg);
  //TODO include calibration

  return true; // if successful
}

bool tilt(int deg) {
  // Tilt to the correct angle - include calibration

  tilt_servo.write(deg);
  //TODO include calibration

  return true; // if successful
}


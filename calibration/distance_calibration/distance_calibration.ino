#include <Servo.h>

Servo pan_servo;
Servo tilt_servo;

const int PAN_PIN = 3;
const int TILT_PIN = 10;


double distance = 0;    // first analog sensor
int inByte = 0;         // incoming serial byte

// Every time you send a character, the arduino prints a value from its analog pin

void setup()
{
  // start serial port at 9600 bps and wait for port to open:
  Serial.begin(9600);
  pan_servo.attach(PAN_PIN);
  tilt_servo.attach(TILT_PIN);
  
  pan(0);
  tilt(0);
}

void loop()
{
  establishContact(); // wait until a keypress comes across the line
  while (Serial.available() > 0) 
  {
    // empty the serial buffer
    inByte = Serial.read();
  }
  distance = analogRead(0); // take a single reading
  Serial.println(distance);
  // and then loop to the top and wait for another keypress
}

void establishContact() {
  while (Serial.available() <= 0) {
    delay(500);
  }
}

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

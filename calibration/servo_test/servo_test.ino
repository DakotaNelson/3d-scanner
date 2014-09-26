#include <Servo.h>

Servo pan_servo;
Servo tilt_servo;

const int PAN_PIN = 3;
const int TILT_PIN = 10;
const int DELAY = 1000;

void setup() {
  pan_servo.attach(PAN_PIN);
  tilt_servo.attach(TILT_PIN);
}

void loop() {
  pan(0);
  tilt(0);
  delay(DELAY);
  
  pan(-30);
  delay(DELAY);
  pan(30);
  delay(DELAY);
  
  tilt(-10);
  delay(DELAY);
  tilt(90);
  delay(DELAY);
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

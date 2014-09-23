
#ifndef SERIAL_RATE
#define SERIAL_RATE         115200
#endif

#ifndef SERIAL_TIMEOUT
#define SERIAL_TIMEOUT      5
#endif 
String inString = "";    // string to hold input


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
}

void scan(int resolution){
  int panMotor = 3;
  int tiltMotor = 10;
  int sensor = A0;
  int column = 64;
  
  analogWrite(panMotor, 64);
  analogWrite(tiltMotor, 64);
  while(column < 128){
    //scan direction 1
    for(int d1 = 64; d1<128; d1++){
      analogWrite(panMotor, d1); //scans one direction horizontally
      //Serial.println(analogRead(sensor));
      Serial.println(d1);
      Serial.println(column);
      delay(100);
    }
    column+=1;
    analogWrite(tiltMotor, column);   //scans up one postion
    //scans direction 2
    for(int d2 = 128; d2>64; d2--){
      analogWrite(panMotor, d2);
      //Serial.println(analogRead(sensor));
      Serial.println(d2);
      Serial.println(column);
      delay(100);
    }
    column+=1;
    analogWrite(tiltMotor, column);   
  }
        
}

void loop() {
  // Read serial input:
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char 
      // and add it to the string:
      inString += (char)inChar; 
    }
    // if you get a newline, print the string,
    // then the string's value:
    if (inChar == '\n') {
      //Serial.println(inString.toInt());
    //resolution is the value sent over serial
  scan(inString.toInt());
    }
 }
}

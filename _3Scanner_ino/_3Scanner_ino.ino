
#ifndef SERIAL_RATE
#define SERIAL_RATE         115200
#endif

#ifndef SERIAL_TIMEOUT
#define SERIAL_TIMEOUT      5
#endif
0;
int column = 64;


String inString = "";    // string to hold input

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
}

void scan(resolution){
  int panMotor = 3;
  int tiltMotor = 10;
  int sensor = A0;
  
  while(column < 128){
    //scan direction 1
    for(int d1 = 64; d1<128; d1++){
      analogWrite(panMotor, d1); //scans one direction horizontally
      analogRead(sensor);
    }
    analogWrite(tiltMotor, column)//scans up one postion
    column++;
    //scans direction 2
    for(int d2 = 128; d2>64; d1--){
      analogWrite(panMotor, d2);
      analogRead(sensor);
    }
    analogWrite(tiltMotor, column);
    column++;
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
      Serial.println(inString.toInt());
    //resolution is the value sent over serial
    scan(inString.toInt());
        // clear the string for new input:
      inString = ""; 
    }
  }
}



double distance = 0;    // first analog sensor
int inByte = 0;         // incoming serial byte

// Every time you send a character, the arduino prints a value from its analog pin

void setup()
{
  // start serial port at 9600 bps and wait for port to open:
  Serial.begin(9600);
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

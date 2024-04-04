//https://www.instructables.com/Using-a-4-digit-7-segment-display-with-arduino/

#include "SevSeg.h"
SevSeg sevseg; //Initiate a seven segment controller object

int numTime = 0;
long int prevInterval = 0;
const long DELAY = 1000;

void setup() {
  byte numDigits = 4;  
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  bool resistorsOnSegments = 0; 
  // variable above indicates that 4 resistors were placed on the digit pins.
  // set variable to 1 if you want to use 8 resistors on the segment pins.
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);

  Serial.begin(9600);
  setTime();
}

void setTime() {
  int minutes = numTime / 60;
  int seconds = numTime % 60;

  int result = minutes * 100 + seconds;
  sevseg.setNumber(result, 2);
}

void loop() {
  if (millis() - prevInterval >= DELAY) {
    prevInterval = millis();
    numTime++;
    Serial.println(numTime);
    setTime();
  }
  sevseg.refreshDisplay(); // Must run repeatedly
}
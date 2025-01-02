#include "SevSeg.h"
SevSeg sevseg; //Initiate a seven segment controller object

int count2display;
int skip;
const int SKIP_WINDOW = 4000;
const int INIT_CNTDOWN = 100;
void setup() {
    byte numDigits = 4;  
    byte digitPins[] = {1, 2, 3, 4};
    byte segmentPins[] = {5, 6, 7, 8, 9, 10, 11, 12};
    bool resistorsOnSegments = 0; 
    // variable above indicates that 4 resistors were placed on the digit pins.
    // set variable to 1 if you want to use 8 resistors on the segment pins.
    sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
    sevseg.setBrightness(100);

    count2display = INIT_CNTDOWN;
    skip = SKIP_WINDOW;
}
void loop()
{
  if (skip==0){
    count2display--;
    if (count2display==0)
      count2display = INIT_CNTDOWN;
    skip = SKIP_WINDOW;
  }
  sevseg.setNumber(count2display);
  sevseg.refreshDisplay(); // Must run repeatedly
  skip--;
}
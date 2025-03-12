#include "SevSeg.h"

// Declarations
SevSeg sevseg;
int analogPin0(A0);
int analogPin1(A1);
int valOflight = 0;
int DARK_TH = 900;//previously 500
unsigned long startTime = 0;
bool timerStarted = false;


//Setup
void setup() 
{
  //Setup 4digit7segment display
  byte numDigits = 4;  //Original: 2
  byte digitPins[] = {1, 2, 3, 4}; //Orginial: 3,4
  byte segmentPins[] = {5, 6, 7, 8, 9, 10, 11, 12};
  bool resistorsOnSegments = 0; 
  // variable above indicates that 4 resistors were placed on the digit pins.
  // set variable to 1 if you want to use 8 resistors on the segment pins.
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(100);
  Serial.begin(9600);
}
//Loop
void loop() 
{
  measure();
  sevseg.refreshDisplay();
}

//Measure Time
void measure()
{ 
  int pin0 = analogRead(analogPin0);
  int pin1 = analogRead(analogPin1);
  // if(pin0 > 900 || pin1 > 900)
  // {
  //   Serial.print(pin1);
  //   Serial.print(" ");
  //   Serial.println(pin0);
  // }
  if ((pin0 <= DARK_TH) && (pin1 <= DARK_TH))
  {
    return;
  }

  //sevseg.setNumber(12);
  if ( pin0 >= DARK_TH && pin1 <=DARK_TH)
  {
    // Serial.println("Debug1 ");
    // Serial.println(timerStarted);
    if (!timerStarted)
    {
      startTime = millis();
      timerStarted = true;
    }
  } 

  if ( pin0 <= DARK_TH && pin1 >= DARK_TH)
  {
    // Serial.println("Debug2 ");
    // Serial.println(timerStarted);
    if (timerStarted)
    {
      unsigned long endTime = millis();
      unsigned long elapsedTime = endTime - startTime;

      unsigned long eseconds = elapsedTime/1000;
      Serial.print("Time taken: ");
      Serial.print(elapsedTime);
      Serial.println(" milliseconds");
      if(eseconds < 1)
        sevseg.setNumber(elapsedTime);
      // else if (eseconds >= 99)
      // {
      //   sevseg.setNumber(99);
      // }
      else
      {
        sevseg.setNumber(eseconds);
      }
      timerStarted = false;
    }
  }
}

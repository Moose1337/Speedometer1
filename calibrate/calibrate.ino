#include "SevSeg.h"

// Declarations
SevSeg sevseg;
int analogPin0(A0);
int analogPin1(A1);
int valOflight = 0;
int slowdown = 5;
int DARK_TH = 700;//previously 500
unsigned long startTime = 0;
bool timerStarted = false;


//Setup
void setup() 
{
  //Setup 4digit7segment display
  byte numDigits = 2;  
  byte digitPins[] = {3, 4};
  byte segmentPins[] = {5, 6, 7, 8, 9, 10, 11, 12};
  bool resistorsOnSegments = 0; 
  // variable above indicates that 4 resistors were placed on the digit pins.
  // set variable to 1 if you want to use 8 resistors on the segment pins.
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(100);
  pinMode(13, INPUT);
  Serial.begin(9600);


}


//Calibrate 
void calibrate()
{
  // slowdown--;
  // if (slowdown==0) {
    valOflight = analogRead(analogPin0);
    int n = valOflight/100;
    Serial.println(n);
    sevseg.setNumber(n);
    // Serial.println("HIGH");
  //}
}


//Measure Time
void measure()
{ 
  int pin0 = analogRead(analogPin0);
  int pin1 = analogRead(analogPin1);
  if ((pin0 >= DARK_TH) && (pin1 >= DARK_TH))
  {
    return;
  }

  //sevseg.setNumber(12);
  if ( pin0 >= DARK_TH)
  {
    if (!timerStarted)
    {
      startTime = millis();
      timerStarted = true;
    }
  } 

  if ( pin1 >= DARK_TH)
  {
    if (timerStarted)
    {
      unsigned long endTime = millis();
      unsigned long elapsedTime = endTime - startTime;

      unsigned int eseconds = elapsedTime/10;
      Serial.print("Time taken: ");
      Serial.print(elapsedTime);
      Serial.println(" milliseconds");
      if (eseconds >= 99)
      {
        sevseg.setNumber(99);
      }
      else
      {
        sevseg.setNumber(eseconds);
      }
      timerStarted = false;
    }
  }

  // Serial.println("LOW");
  // slowdown = 5;
  // }
}


//Loop
void loop() 
{
  if(digitalRead(13) == HIGH)
  {
    calibrate();
  }
  else 
  {
    measure();
  }
  sevseg.refreshDisplay();
}


// Define pin connections
const int ledPin1 = 13;  // LED pin 1
const int ledPin2 = 13;  // LED pin 2 // orginally 12
const int sensor1Pin = 7;  // Sensor 1 pin
const int sensor2Pin = 6;  // Sensor 2 pin

unsigned long startTime = 0;  // Start time of timer
bool timerStarted = false;  // Flag to track if timer has started

void setup() {
  // Initialize pins as output/input
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(sensor1Pin, INPUT);
  pinMode(sensor2Pin, INPUT);

  // Start serial monitor
  Serial.begin(9600);
}

void loop() {
  // Make LED glow forever
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);

  // Check sensor 1
  if (digitalRead(sensor1Pin) == HIGH)
  {  // Adjusted logic
    // Start timer if sensor 1 detects LED glow
    if (!timerStarted)
    {
      startTime = millis();
      timerStarted = true;
    }
  } 
  // else if (digitalRead(sensor1Pin) == LOW && timerStarted == false)
  // {
  //   // Reset timer if sensor 1 does not detect LED glow
  //   timerStarted = false;
  // }

  // Check sensor 2
  if (digitalRead(sensor2Pin) == HIGH)
  {  // Adjusted logic
    // End timer if sensor 2 detects LED glow
    if (timerStarted)
    {
      unsigned long endTime = millis();
      unsigned long elapsedTime = endTime - startTime;
      // if (elapsedTime != 0)
      // {
      // Calculate and print time
      Serial.print("Time taken: ");
      Serial.print(elapsedTime);
      Serial.println(" milliseconds");
      // }
      timerStarted = false;
  
    }
  }
}
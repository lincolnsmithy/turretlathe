#include <Wire.h>

// these constants won't change:
int ledPin = D1;      // LED connected to digital pin 13
int irEmit = D5;
int irRec = D4;

int rpm = 0;


long lastUpdate = 10;  // for timing display updates
volatile long accumulator = 0;  // sum of last 8 revolution times
volatile unsigned long startTime = 0; // start of revolution in microseconds
volatile unsigned int revCount = 0; // number of revolutions since last display update
 



// these variables will change:
int sensorReading = 0;      // variable to store the value read from the sensor pin
int ledState = LOW;         // variable used to store the last LED status, to toggle the light

void setup() {
  //pinMode(irEmit, OUTPUT);
  pinMode(irRec, INPUT_PULLUP);// declare the ledPin as as OUTPUT
  Serial.begin(9600);  // use the serial port
  attachInterrupt(digitalPinToInterrupt(irRec), tach_interrupt, FALLING);
  //digitalWrite(irEmit, HIGH);
  Particle.variable("rpm", rpm);

}

void loop() {
  // read the sensor and store it in the variable sensorReading:
  
  Serial.print("irREC: ");
  Serial.println(digitalRead(irRec));
  
  delay(100);  // delay to avoid overloading the serial port buffer

  if (millis() - lastUpdate > 1000) // update every second
  {
    rpm = 0;
    // divide number of microseconds in a minute, by the average interval.
    if (revCount > 0)
    {
      rpm = 60000000 / (accumulator>>3);
    }
    //Particle.publish("rpm",rpm);
    Serial.print("RPM: ");
    Serial.println(rpm);
    
    //matrix.println(rpm);
    //matrix.writeDisplay();
    
    lastUpdate = millis();
    revCount = 0;
  }

}

void tach_interrupt()
{
  // calculate the microseconds since the last interrupt
  long usNow = micros();
  long elapsed = usNow - startTime;
  startTime = usNow;  // reset the clock
  
  // Accumulate the last 8 interrupt intervals
  accumulator -= (accumulator >> 3);
  accumulator += elapsed;
  revCount++;
}
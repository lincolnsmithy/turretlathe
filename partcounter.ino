int buttonPin = D0;         // the number of the input pin
int ledPin = D1;       // the number of the output pin

int state = HIGH;      // the current state of the output pin
int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin
int count = -1;

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long mytime = 0;         // the last time the output pin was toggled
unsigned long debounce = 50;   // the debounce time, increase if the output flickers

void setup()
{
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

}

void loop()
{
  Particle.variable("count",count);
  
  reading = digitalRead(buttonPin);

  // if the input just went from LOW and HIGH and we've waited long enough
  // to ignore any noise on the circuit, toggle the output pin and remember
  // the time
if (reading == HIGH  && previous == LOW && (millis() - mytime) > debounce) {
  Serial.println("MYTIME:");
  Serial.println(mytime);
  Serial.println(millis() - mytime);
  Serial.println(reading);
  Serial.println(count);
  if (state == HIGH)
  {
    count = count + 1;
    state = LOW;
    mytime = millis();
  }
  else
  {
    count = count + 1;
    state = HIGH;
    mytime = millis();    
  }
}


else
{
  if (state == LOW)
  {
    
    state = LOW;
    //Serial.println("LOW");
    digitalWrite(ledPin,state);
  }
  else 
  {
    
    state = HIGH;
    //Serial.println("HIGH");
    digitalWrite(ledPin, state);
  }
}
 //Serial.println(buttonPin);
  // 
   //Serial.println(reading);
previous = reading;
} 
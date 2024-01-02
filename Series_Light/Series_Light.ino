const int ledBlue = 4;
const int ledyellow = 5;
const int ledred = 18;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(ledBlue, OUTPUT);
  pinMode(ledyellow, OUTPUT);
  pinMode(ledred, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(ledBlue, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(ledyellow, HIGH); 
  digitalWrite(ledBlue, LOW);    // turn the LED off by making the voltage LOW
  delay(100);               // wait for a second
  digitalWrite(ledred, HIGH); 
  digitalWrite(ledyellow, LOW); 
  delay(100); 
  digitalWrite(ledred, LOW);      
}

#define LEDPin  5

void setup() 
{
  pinMode(LEDPin, OUTPUT);
   
}

void loop() 
{ 
  for(uint16_t j=0; j<20000; j=j+200)
  {
    digitalWrite(LEDPin, HIGH);
    delayMicroseconds(j);
    digitalWrite(LEDPin, LOW);
    delayMicroseconds(20000-j);    
  }
  
 for(uint16_t j=20000; j>0; j=j-200)
  {
    digitalWrite(LEDPin, HIGH);
    delayMicroseconds(j);
    digitalWrite(LEDPin, LOW);
    delayMicroseconds(20000-j);    
  }

}

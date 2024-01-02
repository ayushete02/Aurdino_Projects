int sensorPin = 2; // select the input pin
int sensorValue = 0; // variable to store the value coming from the sensor
 
void setup ()
{
pinMode(BUILTIN_LED, OUTPUT); // Initialize the BUILTIN_LED pin as an output
Serial.begin (9600);
}
 
void loop ()
{
sensorValue = analogRead (sensorPin);
Serial.println (sensorValue, DEC); //debug
if(sensorValue <= 100)
{
digitalWrite (BUILTIN_LED, HIGH); //led off
delay(1000);
}
digitalWrite (BUILTIN_LED, LOW); //led on - default
}

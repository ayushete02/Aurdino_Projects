#include "DHT.h"
#define DHT11PIN 4
int LED = 2;

DHT dht(DHT11PIN, DHT11);
void setup()
{

  Serial.begin(115200);
  pinMode (LED, OUTPUT);
  dht.begin();
}

void loop() {
  float temp = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println("ºC ");
  delay(500);

//  threshold temperature is 40ºC
  if (temp > 40) {
    digitalWrite(LED, HIGH);
  }
  else {
    digitalWrite(LED, LOW);
  }
}

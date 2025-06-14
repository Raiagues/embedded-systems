#include <SimpleDHT.h>

#define PIN_SENSOR 8
 
SimpleDHT11 sensor;

void setup() {
  Serial.begin(9600);
}

void loop() {
  byte temp = 0;
  byte hum = 0;
  byte data[40] = {0};

  int result = sensor.read(PIN_SENSOR, &temp, &hum, data);
  
  Serial.print("Temperature : "); Serial.print((int)temp); Serial.print("ºC, ");
  Serial.print("Humidity : "); Serial.print((int)hum); Serial.println("%");

  delay(1000);
}
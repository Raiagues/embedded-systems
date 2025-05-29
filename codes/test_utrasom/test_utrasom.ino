#include <SR04.h>
#define ECHO_PIN 13
#define TRIG_PIN 12
#define RED_PIN 11
#define YELLOW_PIN 10
#define GREEN_PIN 9

SR04 sensor = SR04(ECHO_PIN, TRIG_PIN);
int distance = 0;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  distance = sensor.Distance();
  Serial.print("Distance : "); Serial.print(distance); Serial.println("cm");
  if(distance <= 3) 
  {
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
  } 
  else if(distance > 3 && distance <= 6) 
  {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(YELLOW_PIN, HIGH);    
    digitalWrite(GREEN_PIN, LOW);
  } 
  else if(distance > 6 && distance <= 10) 
  {
    digitalWrite(YELLOW_PIN, LOW);    
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);    
  } 
  else 
  {
    digitalWrite(RED_PIN, LOW);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
  }

  delay(500);
}

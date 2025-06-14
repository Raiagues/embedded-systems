#include <Servo.h>
#define RED 12
#define YELLOW 7
#define GREEN 4

Servo myservo;

int pos = 0;

void setup() {
  myservo.attach(9);
  pinMode(RED, INPUT);
  pinMode(YELLOW, INPUT);
  pinMode(GREEN, INPUT);
  Serial.begin(9600);
}

void loop() {
  for(pos = 0; pos <= 180; pos++) 
  {
    if(((pos>=0) && (pos<40)) || ((pos>140) && (pos<=180))) 
    {
      digitalWrite(RED, HIGH);
      digitalWrite(YELLOW, LOW);
      digitalWrite(GREEN, LOW);
    } else if(((pos>=40) && (pos<70)) || ((pos>110) && (pos<140))) 
    {
      digitalWrite(RED, LOW);
      digitalWrite(YELLOW, HIGH);
      digitalWrite(GREEN, LOW);
    } else if(((pos>=70) && (pos<110))) 
    {
      digitalWrite(RED, LOW);
      digitalWrite(YELLOW, LOW);
      digitalWrite(GREEN, HIGH);
    }
    myservo.write(pos);
    Serial.println(pos);
    delay(15);
  }
  for(pos = 180; pos >= 0; pos--) 
  {
    if(((pos>=0) && (pos<40)) || ((pos>140) && (pos<=180))) 
    {
      digitalWrite(RED, HIGH);
      digitalWrite(YELLOW, LOW);
      digitalWrite(GREEN, LOW);
    } else if(((pos>=40) && (pos<70)) || ((pos>110) && (pos<140))) 
    {
      digitalWrite(RED, LOW);
      digitalWrite(YELLOW, HIGH);
      digitalWrite(GREEN, LOW);
    } else if(((pos>=70) && (pos<110))) 
    {
      digitalWrite(RED, LOW);
      digitalWrite(YELLOW, LOW);
      digitalWrite(GREEN, HIGH);
    }
    myservo.write(pos);
    Serial.println(pos);
    delay(15);
  }
  
}

#include <Servo.h>

#define RED 12
#define YELLOW 7
#define GREEN 4
#define BUTTON 3
#define SERVO 9

Servo myservo;
int pos = 0;
int buttonState  = 0;
int direction = 1;

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BUTTON, INPUT);
  myservo.attach(SERVO);
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(BUTTON);

  if(buttonState == 0) 
  {
    if(pos >= 180) {
      direction = -1;
    } 
    else if(pos <=0)
    {
      direction = 1;
    }
    pos+=30*direction;
    myservo.write(pos);
    Serial.println(pos);
    delay(500);
  }
  
  if(((pos >= 0) && (pos < 30)) || ((pos > 150) && (pos <= 180))){
    digitalWrite(RED, HIGH);
    digitalWrite(YELLOW, LOW);
    digitalWrite(GREEN, LOW);
  }
  if(((pos >= 30) && (pos < 70)) || ((pos >= 110) && (pos < 150))){
    digitalWrite(RED, LOW);
    digitalWrite(YELLOW, HIGH);
    digitalWrite(GREEN, LOW);
  }
  if ((pos >= 70) && (pos < 110)) {
    digitalWrite(RED, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(GREEN, HIGH);
  }
}

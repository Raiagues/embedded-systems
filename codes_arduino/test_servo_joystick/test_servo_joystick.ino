#include <Servo.h>

#define RED 12
#define YELLOW 7
#define GREEN 4

#define BUTTON 3
#define SERVO 9

#define X A1
#define Y A0

Servo myservo;
int posx;
int posy;
int pos;
int buttonState  = 0;
int direction = 1;

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);

  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(X, INPUT);
  pinMode(Y, INPUT);

  digitalWrite(BUTTON, HIGH);
  myservo.attach(SERVO);

  Serial.begin(9600);
}

void loop() {

  buttonState = digitalRead(BUTTON);
  Serial.print("Button : ");
  Serial.println(buttonState);

  Serial.print("X : ");
  posx = analogRead(X);
  Serial.println(posx);

  Serial.print("Y : ");
  posy = analogRead(Y);
  Serial.println(posy);

  // switch the value from 0-1023 to 0-180
  pos = map(posx, 0, 1023, 0, 180);
  myservo.write(pos);


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
  delay(150);
}

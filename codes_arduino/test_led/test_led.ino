#define LED_RED 13
#define LED_YELLOW 12
#define LED_GREEN 11
#define LED_BLUE 10
#define LED_WHITE 9
#define INCREASE true
#define DECREASE false

unsigned int i;
bool control;

void setup() {
  pinMode(LED_RED, OUTPUT);
  //pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  //pinMode(LED_WHITE, OUTPUT);
  //i = 0;
  //control = INCREASE;
  Serial.begin(9600);
}

void loop() {
  
  digitalWrite(LED_WHITE, LOW);
  digitalWrite(LED_RED, HIGH);
  delay(1000);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, HIGH);
  delay(1000);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, HIGH);
  delay(1000);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, HIGH);
  delay(1000);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_WHITE, HIGH);
  delay(1000);
 
  /*analogWrite(LED_RED,i);
  Serial.println(i);

  if(control == INCREASE) 
  {
    i++;
    if(i == 255)
    {
      control = DECREASE;
    }
  } else if(control == DECREASE) 
  {
    i--;
    if(i == 0)
    {
      control = INCREASE;
    }
  }
  delay(10);*/
/*
  analogWrite(LED_RED, 255);
  analogWrite(LED_GREEN, 0);
  analogWrite(LED_BLUE, 0);
  Serial.println("RED");
  delay(1000);

  analogWrite(LED_RED, 0);
  analogWrite(LED_GREEN, 255);
  analogWrite(LED_BLUE, 0);
  Serial.println("GREEN");
  delay(1000);

  analogWrite(LED_RED, 0);
  analogWrite(LED_GREEN, 0);
  analogWrite(LED_BLUE, 255);
  Serial.println("BLUE");
  delay(1000);*/
}

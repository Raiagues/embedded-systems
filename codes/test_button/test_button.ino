#define BUTTON 9
//#define LED_BLUE 11

#define LED_RED 13
#define LED_YELLOW 12
#define LED_GREEN 11

void setup() {
  pinMode(BUTTON, OUTPUT);
  // pinMode(LED_BLUE, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int buttonState = digitalRead(BUTTON);

  /*if(buttonState) 
  {
    digitalWrite(LED_BLUE, HIGH);
  } else
  {
    digitalWrite(LED_BLUE, LOW);
  }*/

  digitalWrite(LED_RED, HIGH);

  if(buttonState) 
  {
    Serial.println("RED");   
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    Serial.println("YELLOW");   

    delay(1000);

    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, HIGH);
    Serial.println("GREEN");   

    delay(3000);

    digitalWrite(LED_GREEN, LOW);
  } 
}

#define LDR A0

#define LED_RED 13
#define LED_YELLOW 12
#define LED_GREEN 11

int ldrValue = 0;

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  ldrValue = analogRead(LDR);


  if(ldrValue < 200) 
  {
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH);  Serial.println(ldrValue);
  } else if((ldrValue >= 200) && (ldrValue < 400)) {
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, HIGH);  
  } else if((ldrValue >= 400) && (ldrValue < 1000)) {
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, HIGH);  
  }
}

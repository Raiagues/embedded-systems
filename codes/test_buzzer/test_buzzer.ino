#define BUZZ 7 

void setup() {
  pinMode(BUZZ, OUTPUT);
}

void loop() {
  tone(BUZZ, 2000); 
  delay(250);
  noTone(BUZZ);
  delay(250);
}

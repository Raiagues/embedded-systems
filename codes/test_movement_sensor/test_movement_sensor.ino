#define PIR 7

int pirValue;

void setup() {
  pinMode(PIR, INPUT);
  Serial.begin(9600);
}

void loop() {
  pirValue = digitalRead(PIR);
  Serial.println(pirValue);
}

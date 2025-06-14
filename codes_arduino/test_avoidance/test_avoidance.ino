#define SENSOR 2

void setup() {
  pinMode(SENSOR, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(digitalRead(SENSOR));
  delay(50);
}

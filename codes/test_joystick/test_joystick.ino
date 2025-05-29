#define SW 2
#define X 0
#define Y 1

void setup() {
  pinMode(SW, INPUT);
  pinMode(X, OUTPUT);
  pinMode(Y, OUTPUT);
  digitalWrite(SW, HIGH);
  Serial.begin(9600);
}

void loop() {
  Serial.print("Button : ");
  Serial.println(digitalRead(SW));

  Serial.print("X : ");
  Serial.println(analogRead(X));

  Serial.print("Y : ");
  Serial.println(analogRead(Y));
}

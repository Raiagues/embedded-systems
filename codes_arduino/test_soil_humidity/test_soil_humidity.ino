#define RED 7
#define GREEN 6
#define SENSOR A0
#define threshold1 380
#define threshold2 200


void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(SENSOR, INPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(SENSOR);
  Serial.println(sensorValue);
  /*if(sensorValue < threshold1)
  {
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, HIGH);
  } 
  else 
  {  
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
  }*/
  if(sensorValue > threshold2)
  {
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, HIGH);
  } 
  else 
  {  
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
  }
  delay(500);
}

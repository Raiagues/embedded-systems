/* 
    A
   ---
F |   | B
  | G |
   ---
E |   | C
  |   |
   ---
    D
*/

// Segment pins (shared between digits)
#define SEG_A 2
#define SEG_B 3
#define SEG_C 4
#define SEG_D 5
#define SEG_E 6
#define SEG_F 7
#define SEG_G 8
#define SEG_DP 9

// Digit selector pins (common cathodes)
#define DIGIT_1 10
#define DIGIT_2 11
#define DIGIT_3 12
#define DIGIT_4 13

#define ECHO_PIN A0
#define TRIG_PIN A1

#define BUZZ_PIN A2

int distance_cm, duration_us;

unsigned long previousMillis = 0, currentMillis = 0;
int centiseconds = 0, seconds = 0, minutes = 0;

bool buzzerTriggered = false;

void setup() {
  pinMode(SEG_A, OUTPUT);
  pinMode(SEG_B, OUTPUT);
  pinMode(SEG_C, OUTPUT);
  pinMode(SEG_D, OUTPUT);
  pinMode(SEG_E, OUTPUT);
  pinMode(SEG_F, OUTPUT);
  pinMode(SEG_G, OUTPUT);
  pinMode(SEG_DP, OUTPUT);

  pinMode(DIGIT_1, OUTPUT);
  pinMode(DIGIT_2, OUTPUT);
  pinMode(DIGIT_3, OUTPUT);
  pinMode(DIGIT_4, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(BUZZ_PIN, INPUT);

  Serial.begin(9600);
}

void loop() {
  // displayDistance();
  //displayClock();
  displayTimer(5);
}

void displayTimer(int alarm) 
{
  currentMillis = millis();

  if (currentMillis - previousMillis >= 10) {

    if (seconds == alarm && !buzzerTriggered) {
      for(int i = 0; i < 10; i++)
      {
        tone(BUZZ_PIN, 1000, 300);  
        delay(300); 
        noTone(BUZZ_PIN);
        delay(200);
      }
      buzzerTriggered = true;
    }

    previousMillis = currentMillis;

    centiseconds++;
    
    if (centiseconds >= 100) {
      centiseconds = 0;
      seconds++;
    }

    if (seconds > alarm) {

      seconds = 0;
      buzzerTriggered = false;  
    }
    
    Serial.print("Time: "); 
    if (seconds < 10) Serial.print("0");
    Serial.print(seconds); Serial.print(":");
    if (centiseconds < 10) Serial.print("0");
    Serial.println(centiseconds);
  }

  int digits[4] = {
    seconds / 10,
    seconds % 10,
    centiseconds / 10,
    centiseconds % 10
  };

  for(int i = 0; i < 4; i++) {
    DisplayDigit(i+1, digits[i]);
  }
}

void displayClock() 
{
  currentMillis = millis();
  // Increment time every 1000ms = 1 second
  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;

    seconds++;

    if (seconds >= 60) {
      seconds = 0;
      minutes++;
    }

    if (minutes >= 60) {
      minutes = 0;
    }

    Serial.print("Time: "); 
    if (minutes < 10) Serial.print("0");
    Serial.print(minutes); Serial.print(":");
    if (seconds < 10) Serial.print("0");
    Serial.println(seconds);
  }

  int digits[4] = {
    minutes / 10,
    minutes % 10,
    seconds / 10,
    seconds % 10
  };

  for(int i = 0; i < 4; i++) 
  {
    DisplayDigit(i+1, digits[i]);
  }
}

void displayDistance() 
{
  // Send a 10µs pulse to the trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Distance = (duration in microseconds) * (speed of sound / 2)
  duration_us = pulseIn(ECHO_PIN, HIGH);

  // Speed of sound = 343 m/s = 0.0343 cm/µs => Distance = duration * 0.01715 = duration / 58
  distance_cm = duration_us/58.00;

  Serial.print("Distance : "); Serial.print(distance_cm); Serial.println("cm");

  // Break the distance into individual digits
  int digit_thousands = distance_cm/1000;
  int digit_hundreds = (distance_cm/100)%10;
  int digit_tens = (distance_cm/10)%10;
  int digit_units = distance_cm%10;

  // Display each digit repeatedly
  for (int i = 0; i < 20; i++) {
    Clear();
    DisplayDigit(1, digit_thousands);
    DisplayDigit(2, digit_hundreds);
    DisplayDigit(3, digit_tens);
    DisplayDigit(4, digit_units);
  }
}

void selectDigit(int digitNumber)
{
  switch(digitNumber)
  {
    case 1:
      digitalWrite(DIGIT_1, LOW);
      digitalWrite(DIGIT_2, HIGH);
      digitalWrite(DIGIT_3, HIGH);
      digitalWrite(DIGIT_4, HIGH);
      break;
    case 2:
      digitalWrite(DIGIT_1, HIGH);
      digitalWrite(DIGIT_2, LOW);
      digitalWrite(DIGIT_3, HIGH);
      digitalWrite(DIGIT_4, HIGH);
      break;
    case 3:
      digitalWrite(DIGIT_1,HIGH);
      digitalWrite(DIGIT_2, HIGH);
      digitalWrite(DIGIT_3, LOW);
      digitalWrite(DIGIT_4, HIGH);
      break;
    case 4:
      digitalWrite(DIGIT_1, HIGH);
      digitalWrite(DIGIT_2, HIGH);
      digitalWrite(DIGIT_3, HIGH);
      digitalWrite(DIGIT_4, LOW);
      break;
    default :
      digitalWrite(DIGIT_1, HIGH);
      digitalWrite(DIGIT_2, HIGH);
      digitalWrite(DIGIT_3, HIGH);
      digitalWrite(DIGIT_4, HIGH);
      break;
    }
}
void Dp()
{
  digitalWrite(SEG_A, LOW);
  digitalWrite(SEG_B, LOW);
  digitalWrite(SEG_C, LOW);
  digitalWrite(SEG_D, LOW);
  digitalWrite(SEG_E, LOW);
  digitalWrite(SEG_F, LOW);
  digitalWrite(SEG_G, LOW);
  digitalWrite(SEG_DP,HIGH);
}
void Num_0()
{
  digitalWrite(SEG_A, HIGH);
  digitalWrite(SEG_B, HIGH);
  digitalWrite(SEG_C, HIGH);
  digitalWrite(SEG_D, HIGH);
  digitalWrite(SEG_E, HIGH);
  digitalWrite(SEG_F, HIGH);
  digitalWrite(SEG_G, LOW);
  digitalWrite(SEG_DP,LOW);
}
void Num_1()
{
  digitalWrite(SEG_A, LOW);
  digitalWrite(SEG_B, HIGH);
  digitalWrite(SEG_C, HIGH);
  digitalWrite(SEG_D, LOW);
  digitalWrite(SEG_E, LOW);
  digitalWrite(SEG_F, LOW);
  digitalWrite(SEG_G, LOW);
  digitalWrite(SEG_DP,LOW);
}
void Num_2()
{
  digitalWrite(SEG_A, HIGH);
  digitalWrite(SEG_B, HIGH);
  digitalWrite(SEG_C, LOW);
  digitalWrite(SEG_D, HIGH);
  digitalWrite(SEG_E, HIGH);
  digitalWrite(SEG_F, LOW);
  digitalWrite(SEG_G, HIGH);
  digitalWrite(SEG_DP,LOW);
}
void Num_3()
{
  digitalWrite(SEG_A, HIGH);
  digitalWrite(SEG_B, HIGH);
  digitalWrite(SEG_C, HIGH);
  digitalWrite(SEG_D, HIGH);
  digitalWrite(SEG_E, LOW);
  digitalWrite(SEG_F, LOW);
  digitalWrite(SEG_G, HIGH);
  digitalWrite(SEG_DP,LOW);
}
void Num_4()
{
  digitalWrite(SEG_A, LOW);
  digitalWrite(SEG_B, HIGH);
  digitalWrite(SEG_C, HIGH);
  digitalWrite(SEG_D, LOW);
  digitalWrite(SEG_E, LOW);
  digitalWrite(SEG_F, HIGH);
  digitalWrite(SEG_G, HIGH);
  digitalWrite(SEG_DP,LOW);
}
void Num_5()
{
  digitalWrite(SEG_A, HIGH);
  digitalWrite(SEG_B, LOW);
  digitalWrite(SEG_C, HIGH);
  digitalWrite(SEG_D, HIGH);
  digitalWrite(SEG_E, LOW);
  digitalWrite(SEG_F, HIGH);
  digitalWrite(SEG_G, HIGH);
  digitalWrite(SEG_DP,LOW);
}
void Num_6()
{
  digitalWrite(SEG_A, HIGH);
  digitalWrite(SEG_B, LOW);
  digitalWrite(SEG_C, HIGH);
  digitalWrite(SEG_D, HIGH);
  digitalWrite(SEG_E, HIGH);
  digitalWrite(SEG_F, HIGH);
  digitalWrite(SEG_G, HIGH);
  digitalWrite(SEG_DP,LOW);
}
void Num_7()
{
  digitalWrite(SEG_A, HIGH);
  digitalWrite(SEG_B, HIGH);
  digitalWrite(SEG_C, HIGH);
  digitalWrite(SEG_D, LOW);
  digitalWrite(SEG_E, LOW);
  digitalWrite(SEG_F, LOW);
  digitalWrite(SEG_G, LOW);
  digitalWrite(SEG_DP,LOW);
}
void Num_8()
{
  digitalWrite(SEG_A, HIGH);
  digitalWrite(SEG_B, HIGH);
  digitalWrite(SEG_C, HIGH);
  digitalWrite(SEG_D, HIGH);
  digitalWrite(SEG_E, HIGH);
  digitalWrite(SEG_F, HIGH);
  digitalWrite(SEG_G, HIGH);
  digitalWrite(SEG_DP,LOW);
}
void Num_9()
{
  digitalWrite(SEG_A, HIGH);
  digitalWrite(SEG_B, HIGH);
  digitalWrite(SEG_C, HIGH);
  digitalWrite(SEG_D, HIGH);
  digitalWrite(SEG_E, LOW);
  digitalWrite(SEG_F, HIGH);
  digitalWrite(SEG_G, HIGH);
  digitalWrite(SEG_DP,LOW);
}

void Clear()  
{
  digitalWrite(SEG_A, LOW);
  digitalWrite(SEG_B, LOW);
  digitalWrite(SEG_C, LOW);
  digitalWrite(SEG_D, LOW);
  digitalWrite(SEG_E, LOW);
  digitalWrite(SEG_F, LOW);
  digitalWrite(SEG_G, LOW);
  digitalWrite(SEG_DP,LOW);
}

void displayNumber(int number) 
{
  switch (number) 
  {
    case 0: Num_0(); break;
    case 1: Num_1(); break;
    case 2: Num_2(); break;
    case 3: Num_3(); break;
    case 4: Num_4(); break;
    case 5: Num_5(); break;
    case 6: Num_6(); break;
    case 7: Num_7(); break;
    case 8: Num_8(); break;
    case 9: Num_9(); break;
    default: Clear(); break;
  }
}

void DisplayDigit(int digitNumber, int number)
{
  selectDigit(digitNumber);
  displayNumber(number);
  delay(1);
  Clear(); 
}

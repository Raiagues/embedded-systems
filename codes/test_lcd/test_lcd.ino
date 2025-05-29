#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define ADDRESS_LCD 0x27
#define SIZE 16
#define LINES 2

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() 
{
  lcd.init();

  lcd.backlight();
  
  lcd.setCursor(3, 0);
  lcd.print("oieerrr");
  lcd.setCursor(0, 1);
  lcd.print("bjss");
}

void loop() 
{
}

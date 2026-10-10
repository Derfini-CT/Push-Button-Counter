#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buttonPin = 2;
unsigned long count = 0;

int buttonState = HIGH;
int lastButtonState = HIGH;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Button Counter");

  lcd.setCursor(0, 1);
  lcd.print("Count: 0");
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        count++;

        lcd.setCursor(0, 1);
        lcd.print("Count:          ");

        lcd.setCursor(7, 1);
        lcd.print(count);
      }
    }
  }

  lastButtonState = reading;
}
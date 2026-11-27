/*
 * PIN Vault Lock System
 * ---------------------
 * Arduino Uno + 16x2 I2C LCD + 5 push buttons + green/red LEDs + buzzer.
 *
 * How it works:
 *  - Buttons 1-4 each control one digit of a 4-digit PIN (press to count 0-9,
 *    hold to scroll quickly).
 *  - The ENTER button checks the PIN.
 *  - Correct PIN  -> green LED on, "Vault Open!"
 *  - Wrong PIN    -> red LED flashes, digits reset, 3 tries allowed
 *  - 3 wrong PINs -> alarm: red LED + buzzer stay on, system locked
 *
 * Simulated in Tinkercad Circuits.
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---------- Hardware ----------
LiquidCrystal_I2C lcd(0x27, 16, 2);   // I2C address 0x27, 16 columns, 2 rows

const int BTN[4] = {2, 3, 4, 5};      // one button per PIN digit
const int ENTER  = 6;                 // submit button
const int GREEN  = 7;                 // "access granted" LED
const int RED    = 8;                 // "access denied" LED
const int BUZZER = 9;                 // alarm buzzer

// ---------- Settings ----------
const int SECRET[4] = {1, 2, 3, 0};   // the correct PIN: 1230
const int MAX_TRIES = 3;              // wrong attempts before lockout
const unsigned long HOLD_DELAY  = 600; // ms before "hold to scroll" starts
const unsigned long REPEAT_RATE = 400; // ms between digits while holding

// ---------- State ----------
int  digits[4] = {0, 0, 0, 0};        // the PIN the user is entering
int  tries     = 0;
bool locked    = false;               // true after too many wrong tries
bool opened    = false;               // true after the correct PIN

// Previous button readings, used to detect a new press (edge detection)
bool prevBtn[4] = {HIGH, HIGH, HIGH, HIGH};
bool prevEnter  = HIGH;

// Timers for the "hold to scroll" feature
unsigned long holdTimer[4] = {0, 0, 0, 0};
bool isHeld[4] = {false, false, false, false};

void setup() {
  Wire.begin();
  delay(1000);
  lcd.init();
  lcd.init();          // called twice: makes the I2C LCD start reliably in Tinkercad
  lcd.backlight();
  delay(200);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vault System");
  lcd.setCursor(0, 1);
  lcd.print("PIN: 0000");

  // INPUT_PULLUP: a button reads LOW when pressed, HIGH when released
  for (int i = 0; i < 4; i++) pinMode(BTN[i], INPUT_PULLUP);
  pinMode(ENTER,  INPUT_PULLUP);
  pinMode(GREEN,  OUTPUT);
  pinMode(RED,    OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

// Shows the digits currently entered on the LCD
void updateLCD() {
  lcd.setCursor(0, 0);
  lcd.print("Enter PIN:      ");
  lcd.setCursor(0, 1);
  lcd.print("PIN: ");
  for (int i = 0; i < 4; i++) lcd.print(digits[i]);
  lcd.print("       ");          // clear leftover characters
}

void loop() {
  // Final states: stay here forever once locked or opened
  if (locked) {
    digitalWrite(RED, HIGH);
    digitalWrite(BUZZER, HIGH);
    return;
  }
  if (opened) {
    digitalWrite(GREEN, HIGH);
    return;
  }

  // ----- Digit buttons -----
  for (int i = 0; i < 4; i++) {
    bool cur = digitalRead(BTN[i]);

    // New press: add 1 to this digit (wraps 9 -> 0)
    if (cur == LOW && prevBtn[i] == HIGH) {
      digits[i] = (digits[i] + 1) % 10;
      holdTimer[i] = millis();
      isHeld[i] = false;
      updateLCD();
    }

    // Button still held: after HOLD_DELAY, keep counting every REPEAT_RATE
    if (cur == LOW && prevBtn[i] == LOW) {
      if (!isHeld[i] && (millis() - holdTimer[i] > HOLD_DELAY)) {
        isHeld[i] = true;
        holdTimer[i] = millis();
      }
      if (isHeld[i] && (millis() - holdTimer[i] > REPEAT_RATE)) {
        digits[i] = (digits[i] + 1) % 10;
        holdTimer[i] = millis();
        updateLCD();
      }
    }
    prevBtn[i] = cur;
  }

  // ----- Enter button (acts when released) -----
  bool curEnter = digitalRead(ENTER);
  if (curEnter == HIGH && prevEnter == LOW) {
    bool match = true;
    for (int i = 0; i < 4; i++) {
      if (digits[i] != SECRET[i]) { match = false; break; }
    }

    if (match) {
      // Correct PIN
      opened = true;
      digitalWrite(GREEN, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0); lcd.print("Pin Accepted");
      lcd.setCursor(0, 1); lcd.print("Vault Open!");
    } else {
      tries++;
      if (tries >= MAX_TRIES) {
        // Too many wrong tries: trigger the alarm
        locked = true;
        lcd.clear();
        lcd.setCursor(0, 0); lcd.print("Alarm!");
        lcd.setCursor(0, 1); lcd.print("System Locked");
      } else {
        // Wrong PIN: show attempts left, flash red LED, reset digits
        lcd.clear();
        lcd.setCursor(0, 0); lcd.print("Pin Rejected");
        lcd.setCursor(0, 1); lcd.print("Try: ");
        lcd.print(tries); lcd.print("/"); lcd.print(MAX_TRIES);
        for (int i = 0; i < 5; i++) {
          digitalWrite(RED, HIGH); delay(300);
          digitalWrite(RED, LOW);  delay(300);
        }
        for (int i = 0; i < 4; i++) digits[i] = 0;
        updateLCD();
      }
    }
  }
  prevEnter = curEnter;
}

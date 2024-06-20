#include <LiquidCrystal_I2C.h>

// Pin definitions
int redLed1 = 3;           // Red LED pin
int greenLed = 8;          // Green LED pin
int buzzer1 = 5;           // Buzzer pin
int gasPin = A0;           // Gas sensor pin

int gasSensorThres = 900;  // Gas sensor threshold value

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  pinMode(redLed1, OUTPUT);  
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer1, OUTPUT);
  pinMode(gasPin, INPUT);
  
  Serial.begin(9600);  // Start the serial communication
  lcd.begin(16, 2);    // Initialize the LCD with 16 columns and 2 rows
  lcd.backlight();     // Turn on the LCD backlight
  lcd.setCursor(0, 0); // Set the cursor to the first column, first row
  lcd.print("Gas Sensor Init"); // Print a message to the LCD
  delay(2000);         // Wait for 2 seconds
  lcd.clear();         // Clear the LCD
}

void loop() {
  int gasSensor = analogRead(gasPin); // Read the gas sensor value

  Serial.print("PPM LEVEL: ");
  Serial.println(gasSensor);  // Print the gas sensor value to the Serial Monitor

  lcd.clear();
  lcd.setCursor(0, 0);  // Set the cursor to the first column, first row
  lcd.print("PPM VALUE: ");
  lcd.print(gasSensor); // Print the gas sensor value to the LCD

  if (gasSensor > gasSensorThres) {
    digitalWrite(redLed1, HIGH);  // Turn on the red LED
    tone(buzzer1, 5000);          // Turn on the buzzer
    digitalWrite(greenLed, LOW);  // Turn off the green LED

    lcd.setCursor(0, 1);  // Set the cursor to the first column, second row
    lcd.print("Alert! PPM"); // Print an alert message to the LCD
  } else {
    digitalWrite(redLed1, LOW);   // Turn off the red LED
    noTone(buzzer1);              // Turn off the buzzer
    digitalWrite(greenLed, HIGH); // Turn on the green LED

    lcd.setCursor(0, 1);  // Set the cursor to the first column, second row
    lcd.print("Normal Level"); // Print a normal message to the LCD
  }

  delay(1000); // Wait for 1 second before repeating the loop
}

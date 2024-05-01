#include <LiquidCrystal.h> // Include LiquidCrystal library
#include <Keypad.h>       // Include Keypad library

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Initialize LCD on Arduino pins 2-7

#define sensor_pin A0     // Rain sensor pin
#define bt_silent A5     // Silent button pin
#define G_led 8          // Green LED pin
#define R_led 9          // Red LED pin
#define buzzer 13        // Buzzer pin

#define ROWS 4           // Number of rows in the keypad
#define COLS 3           // Number of columns in the keypad

char keys[ROWS][COLS] = {  // Define keypad layout
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {A1, A2, A3, A4}; // Keypad row pins
byte colPins[COLS] = {10, 11, 12};     // Keypad column pins

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); // Initialize keypad

int adc_value;
int percent_value;
int silent = 0;

const char* password = "1234"; // Define the password

void setup() {
  pinMode(sensor_pin, INPUT);       // Set sensor pin as input
  pinMode(bt_silent, INPUT_PULLUP); // Set silent button pin as input with internal pull-up resistor
  pinMode(R_led, OUTPUT);           // Set red LED pin as output
  pinMode(G_led, OUTPUT);           // Set green LED pin as output
  pinMode(buzzer, OUTPUT);          // Set buzzer pin as output

  lcd.begin(16, 2);                 // Initialize LCD with 16 columns and 2 rows
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter Password:");
  lcd.setCursor(0,1);
}

void loop() {
  static char enteredPassword[5]; // Buffer to store entered password
  static int passwordIndex = 0;   // Index for current character in entered password
  
  char key = keypad.getKey(); // Read key from keypad
  
  if (key != NO_KEY) { // If a key is pressed
    if (key == '#' && passwordIndex > 0) { // If '#' key is pressed and password is not empty
      enteredPassword[passwordIndex] = '\0'; // Null-terminate the entered password
      if (strcmp(enteredPassword, password) == 0) { // If entered password matches
        lcd.clear();
        lcd.print("Access Granted");
        delay(1000);
        lcd.clear();
        passwordIndex = 0; // Reset password input
        monitorRain(); // Call the function to monitor rain
        return; // Exit loop to proceed to rain sensor monitoring
      } else {
        lcd.clear();
        lcd.print("Access Denied");
        delay(1000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Enter Password:");
        lcd.setCursor(0, 1);
        passwordIndex = 0; // Reset password input
      }
    } else if (passwordIndex < 4) { // If password length is less than 4 characters
      enteredPassword[passwordIndex++] = key; // Store entered key in password buffer
      lcd.setCursor(passwordIndex - 1, 1); // Move cursor to correct position
      lcd.print(key); // Display entered character on LCD
    }
  }
}

void monitorRain() {
  while (true) {
    adc_value = analogRead(sensor_pin);            // Read sensor value
    percent_value = map(adc_value, 0, 1023, 100, 0); // Map sensor value to percentage
    
    if (digitalRead(bt_silent) == LOW) { // Check if silent button is pressed
      silent = 1;
      delay(100);
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Rain Level: ");
    lcd.print(percent_value);
    lcd.print("%  ");

    lcd.setCursor(0, 1);
    if (percent_value > 30) { // Check if rain level is above threshold
      if (silent == 0) {
        digitalWrite(buzzer, HIGH); // Activate buzzer
      }
      lcd.print("Rain Alert...!!!");
      digitalWrite(G_led, LOW); // Turn off green LED
      digitalWrite(R_led, HIGH); // Turn on red LED
      delay(300);
    } else {
      silent = 0;
      lcd.print(".....Normal.....");
      digitalWrite(G_led, HIGH); // Turn on green LED
      digitalWrite(R_led, LOW);  // Turn off red LED
    }

    digitalWrite(buzzer, LOW); // Deactivate buzzer
    delay(100);
  }
}
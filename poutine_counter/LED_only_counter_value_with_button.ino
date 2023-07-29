#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif

#define PIN 9
#define BUTTON_PIN 21 // The pin to which the button is connected

// MATRIX DECLARATION:
// ... (rest of the code remains unchanged)

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

int counter = 0; // The counter variable to keep track of the value
bool buttonWasPressed = false; // Variable to track the previous button state

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(255);
  matrix.setTextColor(matrix.Color(255, 0, 0)); // Set text color to red
  
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Set the button pin as input with internal pull-up resistor
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
}

void loop() {
  // Check if the button is pressed (active low)
  bool buttonIsPressed = (digitalRead(BUTTON_PIN) == LOW);

  // Check if the button is pressed and was not pressed before
  if (buttonIsPressed && !buttonWasPressed) {
    // Increment the counter when the button is initially pressed
    counter++;

    // Update the display with the new counter value
    updateDisplay();
  }

  // Update the previous button state
  buttonWasPressed = buttonIsPressed;
}

void updateDisplay() {
  matrix.fillScreen(0);
  
  // Convert the counter value to a string for display
  char counterStr[6]; // Assuming the counter won't exceed 99999
  snprintf(counterStr, sizeof(counterStr), "%d", counter);
  
  // Calculate the center x-coordinate for the text
  int textWidth = strlen(counterStr) * 6; // Assuming each character is 6 pixels wide
  int centerX = (matrix.width() - textWidth) / 2;
  
  matrix.setCursor(centerX, 0); // Set cursor to the calculated x-coordinate
  matrix.print(counterStr);
  matrix.show();

  // Send the counter value to the Serial Monitor
  Serial.print("Counter: ");
  Serial.println(counter);
}

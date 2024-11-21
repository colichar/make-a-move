#include <Arduino.h>

// Define the built-in LED pin
#define LED_PIN 13

void setup() {
    pinMode(LED_PIN, OUTPUT); // Set the LED pin as an output
    Serial.begin(9600);       // Start the serial communication at 9600 baud rate
    Serial.println("Arduino program started!");
}

void loop() {
    digitalWrite(LED_PIN, HIGH); // Turn the LED on
    Serial.println("LED is ON");
    delay(1000);                // Wait for 1 second
    digitalWrite(LED_PIN, LOW); // Turn the LED off
    Serial.println("LED is OFF");
    delay(1000);                // Wait for 1 second
}

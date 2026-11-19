#include <Arduino.h>

#define LED_PIN 2

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Hochdimmen (0 = aus, 255 = maximale Helligkeit)
  for (int helligkeit = 0; helligkeit <= 255; helligkeit++) {
    analogWrite(LED_PIN, helligkeit);
    delay(5);
  }

  // Runterdimmen
  for (int helligkeit = 255; helligkeit >= 0; helligkeit--) {
    analogWrite(LED_PIN, helligkeit);
    delay(5);
  }
}
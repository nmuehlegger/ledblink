#include <Arduino.h>

#define LED_PIN 2

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("ESP32 gestartet!");
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED an");
  delay(1000);
  
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED aus");
  delay(1000);
}
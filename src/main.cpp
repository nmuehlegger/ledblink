#include <Arduino.h>
#include "BluetoothA2DPSink.h"

#define LED_PIN 2  // Interne LED (oder z. B. 16 für eine externe LED)

BluetoothA2DPSink a2dp_sink;

// Diese Funktion wird automatisch ausgelöst, wenn du am Handy die Lautstärke änderst
void volume_changed(int volume) {
  // Bluetooth-Lautstärke geht von 0 bis 127 -> auf PWM (0 bis 255) skalieren
  int helligkeit = map(volume, 0, 127, 0, 255);
  analogWrite(LED_PIN, helligkeit);

  Serial.print("Handy-Lautstärke: ");
  Serial.print(volume);
  Serial.print(" / 127  -->  LED-PWM: ");
  Serial.println(helligkeit);
}

// Optional: LED ausschalten, wenn die Bluetooth-Verbindung getrennt wird
void connection_state_changed(esp_a2d_connection_state_t state, void *ptr) {
  if (state == ESP_A2D_CONNECTION_STATE_DISCONNECTED) {
    analogWrite(LED_PIN, 0);
    Serial.println("Bluetooth getrennt - LED aus.");
  } else if (state == ESP_A2D_CONNECTION_STATE_CONNECTED) {
    Serial.println("Erfolgreich als Kopfhörer verbunden!");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  analogWrite(LED_PIN, 0);

  // Callbacks registrieren
  a2dp_sink.set_on_volumechange(volume_changed);
  a2dp_sink.set_on_connection_state_changed(connection_state_changed);

  // ESP32 unter diesem Namen als Bluetooth-Audiogerät sichtbar machen
  a2dp_sink.start("ESP32");
  
  Serial.println("Bereit! Suche am Handy nach 'ESP32 LED-Kopfhoerer'.");
}

void loop() {
  // Alles läuft eventbasiert im Hintergrund über den Bluetooth-Stack
  delay(100);
}